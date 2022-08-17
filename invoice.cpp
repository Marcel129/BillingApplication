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
    bool isConverted = false;
    InvoiceRecord rec(n,
                      q.toUInt(&isConverted),
                      p.toDouble(&isConverted),
                      r.toDouble(&isConverted));
    if(isConverted){
        records.push_back(rec);
        return true;
    }
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
    paymentDeadline = "";


}

const QVector<InvoiceRecord> &invoice::getRecords() const
{
    return records;
}

void invoice::setRecords(const QVector<InvoiceRecord> &newRecords)
{
    records = newRecords;
}

const customer &invoice::getBuyer() const
{
    return buyer;
}

void invoice::setBuyer(const customer &newBuyer)
{
    buyer = newBuyer;
}

void invoice::setBuyer(const QString &newBuyer)
{
    qDebug()<<"Ustawiono odbiorce: "<<newBuyer;
    for(const customer & c: mDatabase->getCustomers()){
        if(c.getName() == newBuyer){
            buyer = c;
        }
    }
}

const QString &invoice::getPaymentMethod() const
{
    return paymentMethod;
}

void invoice::setPaymentMethod(const QString &newPaymentMethod)
{
    paymentMethod = newPaymentMethod;
}

QString invoice::getBillingPalce() const
{
    return billingPalce;
}

void invoice::setBillingPalce(const QString &newBillingPalce)
{
    billingPalce = newBillingPalce;
}

const QDate &invoice::getSaleDate() const
{
    return saleDate;
}

void invoice::setSaleDate(const QDate &newSaleDate)
{
    saleDate = newSaleDate;
}

void invoice::setSaleDate(const QString &newSaleDate)
{
    QString a = newSaleDate;
    saleDate = QDate::fromString(a, "d.M.yyyy");
}

const QString &invoice::getPaymentDeadline() const
{
    return paymentDeadline;
}

void invoice::setPaymentDeadline(const QString &newPaymentDeadline)
{
    paymentDeadline = newPaymentDeadline;
}

const seller &invoice::getSeller() const
{
    return Seller;
}

void invoice::setSeller(const seller &newSeller)
{
    Seller = newSeller;
}

void invoice::setSeller(const QString &newSeller)
{
    for(const seller & c: mDatabase->getSellers()){
        if(c.getName() == newSeller){
            Seller = c;
        }
    }
}

const reciper &invoice::getRecip() const
{
    return recip;
}

void invoice::setRecip(const reciper &newRecip)
{
    recip = newRecip;
}

void invoice::setRecip(const QString &newRecip)
{
    for(const reciper & r: buyer.getRecipers()){
        if(r.getName() == newRecip){
            recip = r;
        }
    }
}

const QDate &invoice::getBillingDate() const
{
    return billingDate;
}

void invoice::setBillingDate(const QDate &newBillingDate)
{
    billingDate = newBillingDate;
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

    QFile mFile(FVpath  + FVLDefaultFileName_Latex);
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
    tmp = "pdflatex -quiet -output-directory=" + FVpath +" " + FVpath + FVLDefaultFileName_Latex;
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
                paymentDeadline);
    createLatexInvoice();
    createPDFInvoice();
    clearData();
}
