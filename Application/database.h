#ifndef DATABASE_H
#define DATABASE_H

#include "config.h"

#include "customer.h"
#include "products.h"
#include "invoicebase.h"

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
    bool loadCustomersFromOldRegister();

    bool getIsLoaded() const;

    const QString getLatestInvoiceNumber();

    const QVector<customer> &getCustomers() const;
    const QVector<seller> &getSellers() const;
    const QVector<product> &getProducts() const;

    void addInvoiceToRegister(const invoiceBase & ai);

    const QVector<oldInvoice> &getInvoicesRegister() const;
    const QVector<oldInvoice> getReversedInvoicesRegister() const;
    void setInvoicesRegister(const QVector<oldInvoice> &newInvoicesRegister);

public slots:
    bool saveInvoicesRegister()const;
    bool saveCustomers()const;
    bool saveSellers()const;
    bool saveProducts()const;
    void pushDatabaseToRemoteRepository()const;

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
    bool removeInvoiceAt(int index);
    bool removeInvoiceFromReversedRegisterAt(int index);
    bool removeReciperAt(int cIndex, int rIndex);

    void refreshRecipersTableView(int);

    const QStringList getCustomersNames()const;
    //returns recipers list for customer
    const QStringList getRecipersNames(const QString & custName);
    const QStringList getSellersNames()const;
    const QStringList getProductsPolishNames(const QString & filter = "") const;
    const QStringList getPaymentMethods()const;

    const QStringList getProductsTypes() const;
    const QStringList getProductsTypesShorts() const;

    const QString getCustomerName(int index);
    const QString getInvoiceNumber_rev(int revIndex);
    const QString getSellerName_rev(int revIndex);
    const QString getCustomerName_rev(int revIndex);
    const QString getCustomerAdress1_rev(int revIndex);
    const QString getCustomerAdress2_rev(int revIndex);
    const QString getCustomerNIP_rev(int revIndex);
    const QString getReciperName_rev(int revIndex);
    const QString getReciperAdress1_rev(int revIndex);
    const QString getReciperAdress2_rev(int revIndex);
    const QString getBillingDate_rev(int revIndex);
    const QString getPaymentMethod_rev(int revIndex);
    const QString getTotalBillingPrice_rev(int revIndex);

    bool updateAvailable()const;


signals:
    void preAddProduct();
    void postAddProduct();
    void preRemoveProduct(int index);
    void postRemoveProduct();
    void preRemoveCustomer(int index);
    void postRemoveCustomer();
    void preRemoveReciper(int index);
    void postRemoveReciper();

    void preRemoveInvoice(int index);
    void postRemoveInvoice();

    void preRemoveBuyer(int index);
    void postRemoveBuyer();
    void preAddBuyer(int index);
    void postAddBuyer();

    void preAddReciper(int index);
    void postAddReciper();

    void refreshRecipersTableViewSignal(int);
    void refreshInvoiceRecordsInRegisterTableViewSignal(int);

};

#endif // DATABASE_H
