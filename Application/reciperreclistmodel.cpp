#include "reciperreclistmodel.h"

ReciperRecListModel::ReciperRecListModel(QObject *parent)
    : QAbstractListModel(parent), mDatabase(nullptr)
{
    actCustomerIndex = 0;
}

int ReciperRecListModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid() || !mDatabase)
        return 0;

    return mDatabase->getCustomers().at(actCustomerIndex).getRecipers().size();
    // FIXME: Implement me!
}

QVariant ReciperRecListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !mDatabase)
        return QVariant();

    const reciper currReciper = mDatabase->getCustomers().at(actCustomerIndex).getRecipers().at(index.row());
    switch(role){
    case LpRole: return QVariant(QString::number(index.row()));
    case reciperName: return QVariant(currReciper.getName());
    case address: return QVariant(currReciper.getAdress());
    case postalCode: return QVariant(currReciper.getPostal_code());
    case town: return QVariant(currReciper.getTown());
    }

    // FIXME: Implement me!
    return QVariant();
}

QHash<int, QByteArray> ReciperRecListModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[LpRole] = "lp";
    names[reciperName] = "reciperName";
    names[address] = "address";
    names[postalCode] = "postalCode";
    names[town] = "town";
    return names;
}

database *ReciperRecListModel::getmDatabase() const
{
    return mDatabase;
}

void ReciperRecListModel::setmDatabase(database *newDatabse)
{
    beginResetModel();
    if(mDatabase){
        mDatabase->disconnect(this);
    }
    mDatabase = newDatabse;

    if(mDatabase){
        connect(mDatabase, &database::preAddReciper, this, [=](){
            const int  index = mDatabase->getCustomers().at(actCustomerIndex).getRecipers().size();
            beginInsertRows(QModelIndex(), index,index);
        });
        connect(mDatabase, &database::postAddReciper, this, [=](){
            endInsertRows();
        });
        connect(mDatabase, &database::preRemoveReciper, this, [=](int index){
            beginRemoveRows(QModelIndex(), index,index);
        });
        connect(mDatabase, &database::postRemoveReciper, this, [=](){
            endRemoveRows();
        });
        connect(mDatabase, &database::refreshRecipersTableViewSignal, this, [=](int index){
            actCustomerIndex = index;
             beginResetModel();
             endResetModel();
        });
    }
    endResetModel();
}

