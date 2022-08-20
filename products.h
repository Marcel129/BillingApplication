#ifndef PRODUCTS_H
#define PRODUCTS_H

#include <QFile>
#include <QString>
#include <QDebug>

#include <config.h>

const int productsElementsCount = 5;

class product
{
    QString type;
    QString latinName;
    QString polishName;
    QString species;
    QString registerNumber;
public:
    product();
    product(const QStringList &);
    const QString &getType() const;
    void setType(const QString &newType);
    const QString &getLatinName() const;
    void setLatinName(const QString &newLatinName);
    const QString &getPolishName() const;
    void setPolishName(const QString &newPolishName);
    const QString &getSpecies() const;
    void setSpecies(const QString &newSpecies);
    const QString &getRegisterNumber() const;
    void setRegisterNumber(const QString &newRegisterNumber);
};

#endif // PRODUCTS_H
