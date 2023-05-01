#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>

#include <customer.h>
#include <config.h>
#include <products.h>
#include <invoicebase.h>
#include <QMessageBox>

class database : public QObject
{
    Q_OBJECT
    bool isLoaded;
    QVector<customer> customers;
    QVector<seller> sellers;
    QVector<product> products;
    QVector<oldInvoice> invoicesRegister;
    QStringList paymentMethods;

    QStringList mProductsTypes;
    QStringList mPoductsTypesShorts;

public:
    explicit database(QObject *parent = nullptr);

    bool loadCustomers();
    bool loadSellers();
    bool loadPaymentMethods();
    bool loadProducts();
    bool loadInvoicesRegister();

    //do not use if not necessery
    bool loadCustomersFromOldRegister();;

    bool getIsLoaded() const;

    const QString getLatestInvoiceNumber();

    const QVector<customer> &getCustomers() const;
    const QVector<seller> &getSellers() const;
    const QVector<product> &getProducts() const;

    void addInvoiceToRegister(const invoiceBase & ai);

public slots:
    bool saveInvoicesRegister()const;
    bool saveCustomers()const;
    bool saveSellers()const;
    bool saveProducts()const;

    void addCustomer(const QString & n,
                     const QString & a,
                     const QString & t,
                     const QString & pc,
                     const QString & NIP);
    void addReciper(const QString & cust,
                    const QString & n,
                    const QString & a,
                    const QString & t,
                    const QString & pc);
    void addProduct(const QString & type,
                    const QString & latinName,
                    const QString & polishName,
                    const QString & species,
                    const QString & registerNumber = "");

    bool removeProductAt(int index);
    bool removeCustomerAt(int index);
    bool removeReciperAt(int cIndex, int rIndex);

    const QStringList getCustomersNames()const;
    //returns recipers list for customer
    const QStringList getRecipersNames(const QString & custName);
    const QStringList getSellersNames()const;
    const QStringList getProductsPolishNames(const QString & filter = "") const;
    const QStringList getPaymentMethods()const;

    const QStringList getProductsTypes() const;
    const QStringList getProductsTypesShorts() const;

    //    void pushDatabase()const{
    //        qInfo()<<"Zapisuję dane, zaczekaj";
    //        system("git add -A");
    //        system("git commit -m\"Saving data after work\"");
    //        system("git push origin main");
    //    }

signals:
    void preAddProduct();
    void postAddProduct();
    void preRemoveProduct(int index);
    void postRemoveProduct();
    void preRemoveCustomer(int index);
    void postRemoveCustomer();
    void preRemoveReciper(int index);
    void postRemoveReciper();
};

#endif // DATABASE_H
