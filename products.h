#ifndef PRODUCTS_H
#define PRODUCTS_H

#include "config.h"

const int productsElementsCount = 5;
const QStringList productsTypes = {
    invoicesSavingFolderPath,
    invoicesSavingFolderPath,
    invoicesSavingFolderPath
};

const QStringList productsTypesShorts = {
    invoicesSavingFolderPath,
    invoicesSavingFolderPath,
    invoicesSavingFolderPath
};

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
