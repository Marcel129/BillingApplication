#include "invoice.h"

invoice::invoice(QSharedPointer<database> d, QObject *parent)
    : QObject{parent}
{
    is_inited = this->invoiceTemplate.load();
    mDatabase = d;
    saleDate = QDate::currentDate();
    billingDate = QDate::currentDate();
    billingPalce = defaultBillingPlace;
    paymentDeadline = QDate::currentDate();
    setNewInvoiceNumber();

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

            //incorrect invoice number
            if(mList.size() < 3){
                qDebug() << "Incorrect invoice number";
                //set creepy number
                invoiceNumber = "0/0/0";
                return;
            }

            if(mList[2] == y){
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
//    invoiceFileName = invoiceFileName.replace("\"","_");
    removeCharactersNotAllowedInAFileName(invoiceFileName);

    qDebug()<<"|"<<invoiceFileName +".tex"<<"|";

    QFile mFile(invoicesFolderPath  + invoiceFileName +".tex");
    if(!mFile.open(QIODevice::ReadWrite)){
        qDebug()<< "Unable to create invoice file";
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

    tmp = "pdflatex -quiet -output-directory=" + invoicesFolderPath +" " + invoicesFolderPath + invoiceFileName+".tex";
    system(tmp.toStdString().c_str());

    for(const QString & a: filesToDelete){
        tmp = "del " +invoicesFolderPath + a;
        system(tmp.toStdString().c_str());
    }
}

void invoice::createInvoice(){

    if(invoicePaymentMethods.size()>0 && invoicePaymentMethods.size() <5){
        if(paymentMethod == invoicePaymentMethods[0]) paymentDeadline = saleDate.addDays(7);
        else if(paymentMethod == invoicePaymentMethods[1]) paymentDeadline = saleDate.addDays(14);
        else if(paymentMethod == invoicePaymentMethods[2]) paymentDeadline = saleDate.addDays(21);
        else if(paymentMethod == invoicePaymentMethods[3]) paymentDeadline = saleDate;
    }
    else {
        qDebug()<< "Unrecognized payment method";
        //on error set creepy date
        paymentDeadline.setDate(1410,7,10);
    }
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
    mDatabase->addInvoiceToRegister(*this);
    clearData();

    setNewInvoiceNumber();
}
