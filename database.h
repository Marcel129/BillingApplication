#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>

#include <customer.h>
#include <config.h>
#include <products.h>
#include <invoicebase.h>

class database : public QObject
{
    Q_OBJECT
    bool isLoaded;
    QVector<customer> customers;
    QVector<seller> sellers;
    QVector<product> products;
    QVector<oldInvoice> invoicesRegister;
    QStringList paymentMethods;

public:
    explicit database(QObject *parent = nullptr);

    bool loadCustomers();
    bool loadSellers();
    bool loadPaymentMethods();
    bool loadProducts();
    bool loadInvoicesRegister();

    bool getIsLoaded() const;

    const QString getLatestInvoiceNumber();

    const QVector<customer> &getCustomers() const;
    const QVector<seller> &getSellers() const;
    const QVector<product> &getProducts() const;

    void addInvoiceToRegister(const invoiceBase & ai);

public slots:
    bool saveInvoicesRegister()const;
    const QStringList getCustomersNames()const;
    //returns recipers list for customer
    const QStringList getRecipersNames(const QString & custName);
    const QStringList getSellersNames()const;
    const QStringList getProductsPolishNames() const;
    const QStringList getPaymentMethods()const;

signals:

};

#endif // DATABASE_H
