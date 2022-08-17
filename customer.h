#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <QDebug>
#include <QFile>
#include <QVector>

const unsigned int reciperElementsCount = 4;
const unsigned int customerElementsCount = 5;
const unsigned int sellerElementsCount = 10;

class reciper{
protected:
    QString name;
    QString adress;
    QString town;
    QString postal_code;
public:
    reciper();
    reciper(const QStringList & r);
    reciper(QString n, QString a, QString t, QString p);

    const QString &getName() const;
    void setName(const QString &newName);
    const QString &getAdress() const;
    void setAdress(const QString &newAdress);
    const QString &getTown() const;
    void setTown(const QString &newTown);
    const QString &getPostal_code() const;
    void setPostal_code(const QString &newPostal_code);
};

class customer : public reciper
{
    QVector<reciper> Recipers;
    QString NIP;
public:
    customer();
    customer(const QStringList & c);
    customer( QVector<reciper> r, QString n);

    const QVector<reciper> &getRecipers() const;
    void setRecipers(const QVector<reciper> &newRecipers);
    const QString &getNIP() const;
    void setNIP(const QString &newNIP);

    void addReciper(const reciper & r);
    void addReciper(QString n, QString a, QString t, QString p);
    bool removeReciper(QString recipName);
    bool removeReciper(const reciper & recip);
    const QStringList getRecipersNames()const;
};

class seller: public reciper{
    QString phoneNumber;
    QString accountNumber;
    QString NIP;
    QString bankName;
    QString bussinessName;
    QString producerNumber;

public:
    seller();
    seller(const QStringList & r);

    const QString &getPhoneNumber() const;
    void setPhoneNumber(const QString &newPhoneNumber);
    const QString &getAccountNumber() const;
    void setAccountNumber(const QString &newAccountNumber);
    const QString &getNIP() const;
    void setNIP(const QString &newNIP);
    const QString &getBankName() const;
    void setBankName(const QString &newBankName);
    const QString &getBussinessName() const;
    void setBussinessName(const QString &newBussinessName);
    const QString &getProducerNumber() const;
    void setProducerNumber(const QString &newProducerNumber);
};


#endif // CUSTOMER_H
