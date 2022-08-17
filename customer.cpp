#include "customer.h"

const QVector<reciper> &customer::getRecipers() const
{
    return Recipers;
}

void customer::setRecipers(const QVector<reciper> &newRecipers)
{
    Recipers = newRecipers;
}

const QString &customer::getNIP() const
{
    return NIP;
}

void customer::setNIP(const QString &newNIP)
{
    NIP = newNIP;
}

void customer::addReciper(const reciper &r){
    Recipers.push_back(r);
}

void customer::addReciper(QString n, QString a, QString t, QString p){
    reciper r(n,a,t,p);
    Recipers.push_back(r);
}

bool customer::removeReciper(QString recipName){
    for(int i=0; i<Recipers.size(); i++){
        if(Recipers[i].getName() == recipName){
            Recipers.erase(Recipers.begin() + i);
            return true;
        }
    }
    return false;
}

bool customer::removeReciper(const reciper &recip){
    for(int i=0; i<Recipers.size(); i++){
        if(Recipers[i].getName() == recip.getName()){
            Recipers.erase(Recipers.begin() + i);
            return true;
        }
    }
    return false;
}

const QStringList customer::getRecipersNames() const{
    QStringList cn;
    for(const auto & r: Recipers){
        cn.push_back(r.getName());
    }
    return cn;
}

customer::customer()
{
    Recipers.clear();
    NIP = "";
    name= "";
    adress= "";
    town= "";
    postal_code= "";
}

customer::customer(const QStringList &c){
    if(c.size() ==customerElementsCount){
        name = c[0];
        adress = c[1];
        town = c[2];
        postal_code = c[3];
        NIP = c[4];
    }
    else{
        qDebug()<<"Failed to create customer";
    }
}

customer::customer(QVector<reciper> r, QString n):Recipers(r), NIP(n){}

const QString &reciper::getAdress() const
{
    return adress;
}

void reciper::setAdress(const QString &newAdress)
{
    adress = newAdress;
}

const QString &reciper::getTown() const
{
    return town;
}

void reciper::setTown(const QString &newTown)
{
    town = newTown;
}

const QString &reciper::getPostal_code() const
{
    return postal_code;
}

void reciper::setPostal_code(const QString &newPostal_code)
{
    postal_code = newPostal_code;
}

reciper::reciper()
{
    name= "";
    adress= "";
    town= "";
    postal_code= "";
}

reciper::reciper(const QStringList &r){
    if(r.size() == reciperElementsCount){
        name = r[0];
        adress = r[1];
        town = r[2];
        postal_code = r[3];
    }
    else{
        qDebug()<<"Failed to create reciper";
    }
}

reciper::reciper(QString n, QString a, QString t, QString p):name(n), adress(a), town(t), postal_code(p){}

const QString &reciper::getName() const
{
    return name;
}

void reciper::setName(const QString &newName)
{
    name = newName;
}

seller::seller()
{
    name= "";
    adress= "";
    town= "";
    postal_code= "";
    phoneNumber = "";
    accountNumber = "";
    NIP = "";
    bankName = "";
    bussinessName = "";
    producerNumber = "";
}

seller::seller(const QStringList &r){
    if(r.size() == sellerElementsCount){
        if(r[0].size() != 0){
            bussinessName=r[0];
            name =r[1];
            adress=r[2];
            town=r[3];
            postal_code=r[4];
            NIP=r[5];
            phoneNumber=r[6];
            accountNumber=r[7];
            bankName=r[8];
            producerNumber=r[9];
        }
    }
}

const QString &seller::getPhoneNumber() const
{
    return phoneNumber;
}

void seller::setPhoneNumber(const QString &newPhoneNumber)
{
    phoneNumber = newPhoneNumber;
}

const QString &seller::getAccountNumber() const
{
    return accountNumber;
}

void seller::setAccountNumber(const QString &newAccountNumber)
{
    accountNumber = newAccountNumber;
}

const QString &seller::getNIP() const
{
    return NIP;
}

void seller::setNIP(const QString &newNIP)
{
    NIP = newNIP;
}

const QString &seller::getBankName() const
{
    return bankName;
}

void seller::setBankName(const QString &newBankName)
{
    bankName = newBankName;
}

const QString &seller::getBussinessName() const
{
    return bussinessName;
}

void seller::setBussinessName(const QString &newBussinessName)
{
    bussinessName = newBussinessName;
}

const QString &seller::getProducerNumber() const
{
    return producerNumber;
}

void seller::setProducerNumber(const QString &newProducerNumber)
{
    producerNumber = newProducerNumber;
}
