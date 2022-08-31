#include "productreclistmodel.h"

ProductRecListModel::ProductRecListModel(QObject *parent)
    : QAbstractListModel(parent), mDatabase(nullptr)
{
}

int ProductRecListModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid() || !mDatabase)
        return 0;

    return mDatabase->getProducts().size();
    // FIXME: Implement me!
}

QVariant ProductRecListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !mDatabase)
        return QVariant();

    const product currProduct = mDatabase->getProducts().at(index.row());
    switch(role){
    case LpRole: return QVariant(QString::number(index.row()));
    case species: return QVariant(currProduct.getSpecies());
    case latinName: return QVariant(currProduct.getLatinName());
    case polishName: return QVariant(currProduct.getPolishName());
    case type: return QVariant(currProduct.getType());
    case evidenceNumber: return QVariant(currProduct.getRegisterNumber());
    }

    // FIXME: Implement me!
    return QVariant();
}

QHash<int, QByteArray> ProductRecListModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[LpRole] = "lp";
    names[species] = "species";
    names[latinName] = "latinName";
    names[polishName] = "polishName";
    names[type] = "type";
    names[evidenceNumber] = "evidenceNumber";
    return names;
}

database *ProductRecListModel::getmDatabase() const
{
    return mDatabase;
}

void ProductRecListModel::setmDatabase(database *newDatabse)
{
    beginResetModel();
    if(mDatabase){
        mDatabase->disconnect(this);
    }
    mDatabase = newDatabse;

    if(mDatabase){
        connect(mDatabase, &database::preInvAddRecord, this, [=](){
            const int  index = mDatabase->getProducts().size();
            beginInsertRows(QModelIndex(), index,index);
        });
        connect(mDatabase, &database::postInvAddRecord, this, [=](){
            endInsertRows();
        });
        connect(mDatabase, &database::preInvRemoveRecord, this, [=](int index){
            beginRemoveRows(QModelIndex(), index,index);
        });
        connect(mDatabase, &database::postInvRemoveRecord, this, [=](){
            endRemoveRows();
        });
    }
    endResetModel();
}

