#include "invoicerecord.h"

const QString &InvoiceRecord::getProductName() const
{
    return productName;
}

void InvoiceRecord::setProductName(const QString &newProductName)
{
    productName = newProductName;
}

const QString &InvoiceRecord::getPKWiU() const
{
    return PKWiU;
}

void InvoiceRecord::setPKWiU(const QString &newPKWiU)
{
    PKWiU = newPKWiU;
}

const QString &InvoiceRecord::getUnit() const
{
    return unit;
}

void InvoiceRecord::setUnit(const QString &newUnit)
{
    unit = newUnit;
}

double InvoiceRecord::getRabat() const
{
    return rabat;
}

void InvoiceRecord::setRabat(double newRabat)
{
    rabat = newRabat;
}

unsigned int InvoiceRecord::getQuantity() const
{
    return quantity;
}

void InvoiceRecord::setQuantity(unsigned int newQuantity)
{
    quantity = newQuantity;
}

double InvoiceRecord::getPrice() const
{
    return price;
}

void InvoiceRecord::setPrice(double newPrice)
{
    price = newPrice;
}

double InvoiceRecord::getTotalValue() const
{
    return totalValue;
}

void InvoiceRecord::setTotalValue(double newTotalValue)
{
    totalValue = newTotalValue;
}

InvoiceRecord::InvoiceRecord(QString pn,
                             unsigned int q,
                             double p,
                             double r ,
                             QString u,
                             QString pk)
{
    productName = pn;
    PKWiU = pk;
    unit = u;
    r >= MIN_RABAT_VALUE &&r <= MAX_RABAT_VALUE ?
                rabat = r : r < MIN_RABAT_VALUE ?
                rabat = MIN_RABAT_VALUE : rabat = MAX_RABAT_VALUE;
    quantity = q;
    p >= MIN_PRICE_VALUE &&p <= MAX_PRICE_VALUE ?
                price = p : p < MIN_PRICE_VALUE ?
                price = MIN_PRICE_VALUE : price = MAX_PRICE_VALUE;
    totalValue = double(quantity)*price - double(quantity)*price*rabat/100.0;
}

InvoiceRecord::InvoiceRecord(const QStringList & l)
{
    if(l.size() >= recordElementsCount){
        productName = l[0];
        PKWiU = l[2];
        unit = l[4];
        rabat = l[1].toDouble();
        quantity = l[3].toUInt();
        price = l[5].toDouble();
        totalValue = l[6].toDouble();
    }
}

QTextStream& operator<<(QTextStream& os, const InvoiceRecord& rec){
    os << rec.getProductName() << FVTableElemSeparator_DefValue <<
          rec.getRabat()<< "\\% " << FVTableElemSeparator_DefValue <<
          rec.getPKWiU()<< FVTableElemSeparator_DefValue  <<
          rec.getQuantity()<< FVTableElemSeparator_DefValue <<
          rec.getUnit()<< FVTableElemSeparator_DefValue <<
          rec.getPrice() << FVTableElemSeparator_DefValue <<
          rec.getTotalValue() << FVTable_EOL_DefValue ;
    return os;
}


