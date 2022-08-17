#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>

#include <customer.h>
#include <config.h>

class database : public QObject
{
    Q_OBJECT
    bool isLoaded;
    QVector<customer> customers;
    QVector<seller> sellers;
    QStringList paymentMethods;

public:
    explicit database(QObject *parent = nullptr);

    bool loadCustomers();
    bool loadSellers();
    bool loadPaymentMethods();
    bool loadProducts();

    bool getIsLoaded() const;

    const QVector<customer> &getCustomers() const;
    const QVector<seller> &getSellers() const;

public slots:

    const QStringList getCustomersNames()const;
    //returns recipers list for customer
    const QStringList getRecipersNames(const QString & custName);
    const QStringList getSellersNames()const;
    const QStringList getPaymentMethods()const;

signals:

};

#endif // DATABASE_H
