#ifndef INVOICERECORD_H
#define INVOICERECORD_H

#include "config.h"

#define MIN_RABAT_VALUE 0
#define MAX_RABAT_VALUE 100
#define MIN_PRICE_VALUE 0
#define MAX_PRICE_VALUE 100000

const QString FVRecord_productName_DefValue("26/06/6418");
const QString FVRecord_PKWiU_DefValue("26/06/6418");
const QString FVRecord_unit_DefValue( "szt.");
const QString FVTableElemSeparator_DefValue(" & ");
const QString FVTable_EOL_DefValue(" \\\\ \\hline");

const int recordElementsCount = 6;

class InvoiceRecord
{
    QString productName;
    QString PKWiU;
    QString unit;
    double rabat;
    unsigned int quantity;
    double price;
    double totalValue;

public:
    InvoiceRecord(
            QString,
            unsigned int,
            double,
            double r = 0,
            QString u=FVRecord_unit_DefValue,
            QString p=FVRecord_PKWiU_DefValue);
    InvoiceRecord(const QStringList &);

    const QString &getProductName() const;
    void setProductName(const QString &newProductName);
    const QString &getPKWiU() const;
    void setPKWiU(const QString &newPKWiU);
    const QString &getUnit() const;
    void setUnit(const QString &newUnit);
    double getRabat() const;
    void setRabat(double newRabat);
    unsigned int getQuantity() const;
    void setQuantity(unsigned int newQuantity);
    double getPrice() const;
    void setPrice(double newPrice);
    double getTotalValue() const;
    void setTotalValue(double newTotalValue);
};

QTextStream& operator<<(QTextStream& os, const InvoiceRecord& rec);


#endif // INVOICERECORD_H
