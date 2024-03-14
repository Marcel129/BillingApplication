#ifndef INVOICE_H
#define INVOICE_H

#include "invoicetemplate.h"
#include "invoicebase.h"
#include "database.h"
#include "config.h"

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

    void setNewInvoiceNumber(const QString  & nin = invoicesSavingFolderPath);
    const QString getNewInvoiceNumber() const;

    void setInvoiceNumber_slot(const QString  & nin = invoicesSavingFolderPath);
    const QString getInvoiceNumber_slot() const;

    bool addRecord(const QString n, const QString  q, const QString p, const QString r);
    bool removeInvRecordAt(int position);

    double getTotalToPay()const{
        double ttp =0;
        for(const auto & r: records){
            ttp += r.getTotalValue();
        }
        return ttp;
    }
    const QString getTotalToPay_String()const{
        return QString::number(getTotalToPay(),'d',2);
    }

signals:
    void preInvAddRecord();
    void postInvAddRecord();
    void preInvRemoveRecord(int index);
    void postInvRemoveRecord();

};

#endif // INVOICE_H
