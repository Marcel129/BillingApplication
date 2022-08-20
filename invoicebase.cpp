#include "invoicebase.h"

const QVector<InvoiceRecord> &invoiceBase::getRecords() const
{
    return records;
}

void invoiceBase::setRecords(const QVector<InvoiceRecord> &newRecords)
{
    records = newRecords;
}

const seller &invoiceBase::getSeller() const
{
    return Seller;
}

void invoiceBase::setSeller(const seller &newSeller)
{
    Seller = newSeller;
}

const customer &invoiceBase::getBuyer() const
{
    return buyer;
}

void invoiceBase::setBuyer(const customer &newBuyer)
{
    buyer = newBuyer;
}

const reciper &invoiceBase::getRecip() const
{
    return recip;
}

void invoiceBase::setRecip(const reciper &newRecip)
{
    recip = newRecip;
}

const QString &invoiceBase::getPaymentMethod() const
{
    return paymentMethod;
}

void invoiceBase::setPaymentMethod(const QString &newPaymentMethod)
{
    paymentMethod = newPaymentMethod;
}

const QString &invoiceBase::getBillingPalce() const
{
    return billingPalce;
}

void invoiceBase::setBillingPalce(const QString &newBillingPalce)
{
    billingPalce = newBillingPalce;
}

const QDate &invoiceBase::getSaleDate() const
{
    return saleDate;
}

void invoiceBase::setSaleDate(const QDate &newSaleDate)
{
    saleDate = newSaleDate;
}

const QDate &invoiceBase::getBillingDate() const
{
    return billingDate;
}

void invoiceBase::setBillingDate(const QDate &newBillingDate)
{
    billingDate = newBillingDate;
}

const QDate &invoiceBase::getPaymentDeadline() const
{
    return paymentDeadline;
}

void invoiceBase::setPaymentDeadline(const QDate &newPaymentDeadline)
{
    paymentDeadline = newPaymentDeadline;
}

const QString &invoiceBase::getInvoiceNumber() const
{
    return invoiceNumber;
}

void invoiceBase::setInvoiceNumber(const QString &newInvoiceNumber)
{
    invoiceNumber = newInvoiceNumber;
}

invoiceBase::invoiceBase()
{

}

bool oldInvoice::getIsPaid() const
{
    return isPaid;
}

void oldInvoice::setIsPaid(bool newIsPaid)
{
    isPaid = newIsPaid;
}

const QDate &oldInvoice::getLastModificationDate() const
{
    return lastModificationDate;
}

void oldInvoice::setLastModificationDate(const QDate &newLastModificationDate)
{
    lastModificationDate = newLastModificationDate;
}

bool oldInvoice::addRecord(const QString n, const QString q, const QString p, const QString r)
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

void oldInvoice::addRecord(const InvoiceRecord &r){
    records.push_back(r);
}

bool invoiceBase::saveInvoiceInRegister() const
{
    QFile mfile(InvoicesRegisterPath);

    if (!mfile.open(QIODevice::Append))
    {
        qDebug() << "Unable to open invoices register";
        return false;
    }

    QTextStream outStream(&mfile);

    outStream << saleDate.toString(inputDateFormat) <<"\n"
              << billingDate.toString(inputDateFormat)<<"\n"
              <<QDate::currentDate().toString(inputDateFormat)<<"\n";

    outStream<<Seller.getBussinessName()<<CSVSplitTag
            <<Seller.getName()<<CSVSplitTag
           <<Seller.getAdress()<<CSVSplitTag
          <<Seller.getPostal_code()<<CSVSplitTag
         <<Seller.getTown()<<CSVSplitTag
        <<Seller.getNIP()<<CSVSplitTag
       <<Seller.getPhoneNumber()<<CSVSplitTag
      <<Seller.getAccountNumber()<<CSVSplitTag
     <<Seller.getBankName()<<CSVSplitTag
    <<Seller.getProducerNumber()<<CSVSplitTag<<"\n";

    outStream<<buyer.getName()<<CSVSplitTag
            <<buyer.getAdress()<<CSVSplitTag
           <<buyer.getPostal_code()<<CSVSplitTag
          <<buyer.getTown()<<CSVSplitTag
         <<buyer.getNIP()<<CSVSplitTag<<"\n";

    if(recip.getName()!=""){
        outStream<<RecipertTag<<CSVSplitTag
                <<recip.getName()<<CSVSplitTag
               <<recip.getAdress()<<CSVSplitTag
              <<recip.getPostal_code()<<CSVSplitTag
             <<recip.getTown()<<CSVSplitTag<<"\n";
    }

    outStream<<paymentMethod<<CSVSplitTag<<"\n";

    for(const auto & r: records){
        outStream<<ProductTag <<CSVSplitTag<< r.getProductName() << CSVSplitTag
                <<r.getRabat()<< CSVSplitTag
               <<r.getPKWiU()<< CSVSplitTag
              <<r.getQuantity()<< CSVSplitTag
             <<r.getUnit()<< CSVSplitTag
            <<r.getPrice() << CSVSplitTag
           <<r.getTotalValue() << CSVSplitTag<<"\n";
    }

    outStream<<paymentDeadline.toString(inputDateFormat)<<"\n";
    outStream<<"NIE"<<"\n";
    outStream<<invoiceNumber<<"\n";

    mfile.close();

    return true;
}
