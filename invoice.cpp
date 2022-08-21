#include "invoice.h"

invoice::invoice(QSharedPointer<database> d, QObject *parent)
    : QObject{parent}
{
    if(!is_inited){
        is_inited = this->invoiceTemplate.load();
        mDatabase = d;
        saleDate = QDate::currentDate();
        billingDate = QDate::currentDate();
        billingPalce = defaultBillingPlace;
        paymentDeadline = QDate::currentDate();
        //        invoiceNumber = defaultInvoiceNumber;
        setNewInvoiceNumber();
//        addRecord("THUJA", "22","12", "6");
    }
    else{
        is_inited = false;
    }
}

bool invoice::isInited() const
{
    return is_inited;
}

void invoice::addRecord(const InvoiceRecord & record){
    this->records.push_back(record);
}

bool invoice::addRecord(const QString n, const QString q, const QString p,  const QString r)
{
    emit preInvAddRecord();

    bool isConverted = false;
    InvoiceRecord rec(n,
                      q.toUInt(&isConverted),
                      p.toDouble(&isConverted),
                      r.toDouble(&isConverted));
    if(isConverted){
        records.push_back(rec);
        emit postInvAddRecord();
        return true;
    }

    emit postInvAddRecord();
    return false;
}

void invoice::setNewInvoiceNumber(const QString &nin){
    //invoice number is calculating automaticly
    if(nin == ""){
        QString newNumber = mDatabase->getLatestInvoiceNumber();
        QDate tmpDate = QDate::currentDate();
        QString m = QString::number(tmpDate.month()),
                y=QString::number(tmpDate.year());

        if(newNumber == ""){
            invoiceNumber = "1/" + m + "/"+y;
        }
        else{
            QStringList mList= newNumber.split("/");
            if(mList[1] == m){
                int in = mList[0].toInt() +1;
                QString d = QString::number(in);
                invoiceNumber = d+"/" + m + "/"+y;
            }
            else{
                invoiceNumber = "1/" + m + "/"+y;
            }
        }
    }
    //invoice number is given apriori
    else{
        invoiceNumber = nin;
    }
    qDebug()<<"numer faktury: "<<invoiceNumber;
}

const QString invoice::getNewInvoiceNumber() const
{
    return invoiceNumber;
}

void invoice::setInvoiceNumber_slot(const QString &nin)
{
    invoiceNumber = nin;
}

const QString invoice::getInvoiceNumber_slot() const
{
    return invoiceNumber;
}

bool invoice::removeInvRecordAt(int position)
{
    emit preInvRemoveRecord(position);

    if(position >=0 && position < records.size()){
        records.erase(records.begin()+position );
        emit postInvRemoveRecord();
        return true;
    }
    emit postInvRemoveRecord();
    return false;
}

void invoice::clearData()
{
    seller s;
    customer c;
    reciper r;

    invoiceTemplate.refresh();

    records.clear();
    Seller = s;
    buyer= c;
    recip = r;
    paymentMethod = "";
    billingPalce= "";
    saleDate = QDate::currentDate();
    billingDate =  QDate::currentDate();
    paymentDeadline =  QDate::currentDate();;
}

void invoice::setBuyer(const QString &newBuyer)
{
    for(const customer & c: mDatabase->getCustomers()){
        if(c.getName() == newBuyer){
            buyer = c;
        }
    }
}

void invoice::setPaymentMethod(const QString &newPaymentMethod)
{
    paymentMethod = newPaymentMethod;
}

QString invoice::getBillingPalce()
{
    return billingPalce;
}

void invoice::setBillingPalce(const QString &newBillingPalce)
{
    billingPalce = newBillingPalce;
}

void invoice::setSaleDate(const QString &newSaleDate)
{
    QString a = newSaleDate;
    saleDate = QDate::fromString(a, inputDateFormat);
}

void invoice::setSeller(const QString &newSeller)
{
    for(const seller & c: mDatabase->getSellers()){
        if(c.getName() == newSeller){
            Seller = c;
        }
    }
}

void invoice::setRecip(const QString &newRecip)
{
    for(const reciper & r: buyer.getRecipers()){
        if(r.getName() == newRecip){
            recip = r;
        }
    }
}

void invoice::setBillingDate(const QString &newBillingDate)
{
    QString a(newBillingDate);
    billingDate = QDate::fromString(a, outputDateFormat);
}

QString invoice::getSellingDate_String(){
    return billingDate.toString(inputDateFormat);
}


void invoice::createLatexInvoice(){

    QString tmpNum = invoiceNumber, tmpBuy =buyer.getName();
    removePolishDiacritics(tmpBuy);
    invoiceFileName = "Rachunek_Nr_" + tmpNum.replace("/",".") + "_" + tmpBuy.replace(" ", "_");

    QFile mFile(FVpath  + invoiceFileName +".tex");
    if(!mFile.open(QIODevice::ReadWrite)){
        qDebug()<< "Unable to create FV file";
        exit(1);
    }

    QTextStream outStream(&mFile);
    outStream.setCodec("UTF-8");
    int counter = 1;

    outStream << this->invoiceTemplate.getPart(Prembula);
    outStream << this->invoiceTemplate.getPart(Header);
    outStream << this->invoiceTemplate.getPart(SellerBuyerDataBeginning);

    if(recip.getName() != ""){
        qDebug()<<"Odbiorca "<<recip.getName();
        outStream << this->invoiceTemplate.getPart(Reciper);
    }

    outStream << this->invoiceTemplate.getPart(SellerBuyerDataEnding);
    outStream << this->invoiceTemplate.getPart(InvoiceNumberText);
    outStream << this->invoiceTemplate.getPart(MainTableBegining);

    for (const InvoiceRecord &r : records)
    {
        outStream << counter++ << FVTableElemSeparator_DefValue << r << "\n";
    }

    outStream << this->invoiceTemplate.getPart(MainTableEnding);
    outStream << this->invoiceTemplate.getPart(MainTableSummmary);
    outStream << this->invoiceTemplate.getPart(PaymentData);
    outStream << this->invoiceTemplate.getPart(Ending);

    mFile.close();
}

void invoice::createPDFInvoice(){
    QString tmp;

    const QVector<QString> filesToDelete =
    {
        invoiceFileName + ".log",
        invoiceFileName + ".tex",
        invoiceFileName + ".aux"
    };

    tmp = "pdflatex -quiet -output-directory=" + FVpath +" " + FVpath + invoiceFileName+".tex";
    system(tmp.toStdString().c_str());

    for(const QString & a: filesToDelete){
        tmp = "del " +FVpath + a;
        system(tmp.toStdString().c_str());
    }
}

void invoice::createInvoice(){
    invoiceTemplate.insertValuesIntoKeywords(
                Seller,
                buyer,
                recip,
                paymentMethod,
                billingPalce,
                billingDate,
                saleDate,
                paymentDeadline,
                invoiceNumber,
                getTotalToPay());
    createLatexInvoice();
    createPDFInvoice();
    //    saveInvoiceInRegister();
    mDatabase->addInvoiceToRegister(*this);
    clearData();

    setNewInvoiceNumber();
}
