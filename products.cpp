#include "products.h"

const QString &product::getType() const
{
    return type;
}

void product::setType(const QString &newType)
{
    type = newType;
}

const QString &product::getLatinName() const
{
    return latinName;
}

void product::setLatinName(const QString &newLatinName)
{
    latinName = newLatinName;
}

const QString &product::getPolishName() const
{
    return polishName;
}

void product::setPolishName(const QString &newPolishName)
{
    polishName = newPolishName;
}

const QString &product::getSpecies() const
{
    return species;
}

void product::setSpecies(const QString &newSpecies)
{
    species = newSpecies;
}

const QString &product::getRegisterNumber() const
{
    return registerNumber;
}

void product::setRegisterNumber(const QString &newRegisterNumber)
{
    registerNumber = newRegisterNumber;
}

product::product()
{
    type = "";
    latinName = "";
    polishName = "";
    species = "";
    registerNumber = "";
}

product::product(const QStringList &pl)
{
    if(pl.size() >= productsElementsCount){
        type = pl[0];
        latinName = pl[1];
        polishName = pl[2];
        species = pl[3];
        registerNumber = pl[4];
    }
}
