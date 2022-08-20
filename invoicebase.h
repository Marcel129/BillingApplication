#ifndef INVOICEBASE_H
#define INVOICEBASE_H

#include <QObject>
#include <QDebug>
#include <QFile>
#include <QVector>
#include <QDate>
#include <QString>

#include <invoicerecord.h>
#include <customer.h>
#include <config.h>

class invoiceBase {

protected:
    QVector<InvoiceRecord> records;
    seller Seller;
    customer buyer;
    reciper recip;
    QString paymentMethod;
    QString billingPalce;
    QDate saleDate;//data sprzedaży
    QDate billingDate;//data wystawienia rachunku
    QDate paymentDeadline;
    QString invoiceNumber;

public:
    invoiceBase();
    const QVector<InvoiceRecord> &getRecords() const;
    void setRecords(const QVector<InvoiceRecord> &newRecords);
    const seller &getSeller() const;
    void setSeller(const seller &newSeller);
    const customer &getBuyer() const;
    void setBuyer(const customer &newBuyer);
    const reciper &getRecip() const;
    void setRecip(const reciper &newRecip);
    const QString &getPaymentMethod() const;
    void setPaymentMethod(const QString &newPaymentMethod);
    const QString &getBillingPalce() const;
    void setBillingPalce(const QString &newBillingPalce);
    const QDate &getSaleDate() const;
    void setSaleDate(const QDate &newSaleDate);
    const QDate &getBillingDate() const;
    void setBillingDate(const QDate &newBillingDate);
    const QDate &getPaymentDeadline() const;
    void setPaymentDeadline(const QDate &newPaymentDeadline);
    const QString &getInvoiceNumber() const;
    void setInvoiceNumber(const QString &newInvoiceNumber);

    bool saveInvoiceInRegister() const;
};


class oldInvoice: public invoiceBase{
    QDate lastModificationDate;
    bool isPaid;

public:
    const QDate &getLastModificationDate() const;
    void setLastModificationDate(const QDate &newLastModificationDate);
     bool addRecord(const QString n, const QString  q, const QString p, const QString r);
     void addRecord(const InvoiceRecord & r);
     bool getIsPaid() const;
     void setIsPaid(bool newIsPaid);
};

#endif // INVOICEBASE_H
