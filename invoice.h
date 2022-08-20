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

#include <invoicetemplate.h>
#include <invoicebase.h>
#include <database.h>
#include <config.h>

class invoice :  public QObject, public invoiceBase
{
    Q_OBJECT

    InvoiceTemplate invoiceTemplate;
    QSharedPointer<database>  mDatabase;

    QString invoiceFileName;

    bool is_inited;
    //creates latex file with invoice, ready to compilation
    void createLatexInvoice();
    //creates PDF file with prepared latex file
    void createPDFInvoice();

public:
    explicit invoice(QSharedPointer<database> d, QObject *parent = nullptr);
    bool isInited()const;

    void addRecord(const InvoiceRecord & record);
    void clearData();

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
    QString getBillingPalce();
    bool addRecord(const QString n, const QString  q, const QString p, const QString r);

    void setNewInvoiceNumber(const QString  & nin = "");
    const QString getNewInvoiceNumber() const;

    void setInvoiceNumber_slot(const QString  & nin = "");
    const QString getInvoiceNumber_slot() const;
signals:

};

#endif // INVOICE_H
