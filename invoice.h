#ifndef INVOICE_H
#define INVOICE_H

#include <QObject>
#include <QDebug>
#include <QFile>
#include <QVector>
#include <QDate>
#include <QString>
#include <QDir>
#include <QSharedPointer>

#include <invoicerecord.h>
#include <invoicetemplate.h>
#include <database.h>
#include <config.h>

class invoice : public QObject
{
    Q_OBJECT
    FVTemplate invoiceTemplate;
    QSharedPointer<database>  mDatabase;

    QVector<InvoiceRecord> records;
    seller Seller;
    customer buyer;
    reciper recip;
    QString paymentMethod;
    QString billingPalce;
    QDate saleDate;//data sprzedaży
    QDate billingDate;//data wystawienia rachunku
    QString paymentDeadline;

    //przenieść tu wszystkie parametry rachunku
    bool is_inited;
    bool isReciperAdded;

    //creates latex file with invoice, ready to compilation
    void createLatexInvoice();
    //creates PDF filr with prepared latex file
    void createPDFInvoice();

public:
    explicit invoice(QSharedPointer<database> d, QObject *parent = nullptr);
    bool isInited()const;
    void addRecord(const InvoiceRecord & record);
//    void setAddingReciper(bool value);
    void clearData();

    const QVector<InvoiceRecord> &getRecords() const;
    void setRecords(const QVector<InvoiceRecord> &newRecords);

    const customer &getBuyer() const;
    void setBuyer(const customer &newBuyer);

    const QString &getPaymentMethod() const;

    const QDate &getSaleDate() const;
    void setSaleDate(const QDate &newSaleDate);

    const QString &getPaymentDeadline() const;
    void setPaymentDeadline(const QString &newPaymentDeadline);

    const seller &getSeller() const;
    void setSeller(const seller &newSeller);

    const reciper &getRecip() const;
    void setRecip(const reciper &newRecip);


    const QDate &getBillingDate() const;
    void setBillingDate(const QDate &newBillingDate);

public slots:
    void createInvoice();
    void setSeller(const QString &newSeller);
    void setSaleDate(const QString &newSaleDate);
    void setRecip(const QString&newRecip);
    void setBuyer(const QString &newBuyer);
    void setBillingPalce(const QString &newBillingPalce);
    void setPaymentMethod(const QString &newPaymentMethod);
    void setBillingDate(const QString &newBillingDate);
    QString getSellingDate_String();
    QString getBillingPalce() const;
signals:

};

#endif // INVOICE_H
