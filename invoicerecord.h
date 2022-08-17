#ifndef INVOICERECORD_H
#define INVOICERECORD_H

#include <QObject>
#include <QFile>
#include <QDebug>
#include <QVector>

#include <config.h>

#define MIN_RABAT_VALUE 0
#define MAX_RABAT_VALUE 100
#define MIN_PRICE_VALUE 0
#define MAX_PRICE_VALUE 100000

const QString FVRecord_productName_DefValue("26/06/6418");
const QString FVRecord_PKWiU_DefValue("26/06/6418");
const QString FVRecord_unit_DefValue( "szt.");
const QString FVTableElemSeparator_DefValue(" & ");
const QString FVTable_EOL_DefValue(" \\\\ \\hline");

struct InvoiceRecord
{
    QString productName;
    QString PKWiU;
    QString unit;
    float rabat;
    unsigned int quantity;
    float price;
    float totalValue;

    InvoiceRecord(QString,unsigned int,float,float,QString,QString);
};

QTextStream& operator<<(QTextStream& os, const InvoiceRecord& rec);


#endif // INVOICERECORD_H
