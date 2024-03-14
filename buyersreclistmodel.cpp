#include "buyersreclistmodel.h"

BuyersRecListModel::BuyersRecListModel(QObject *parent)
    : QAbstractListModel(parent), mDatabase(nullptr)
{
}

int BuyersRecListModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid() || !mDatabase)
        return 0;

    return mDatabase->getCustomers().size();
    // FIXME: Implement me!
}

QVariant BuyersRecListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !mDatabase)
        return QVariant();

    const customer currBuyer = mDatabase->getCustomers().at(index.row());
    switch(role){
    case LpRole: return QVariant(QString::number(index.row()));
    case buyerName: return QVariant(currBuyer.getName());
    case adress: return QVariant(currBuyer.getAdress());
    case town: return QVariant(currBuyer.getTown());
    case postalCode: return QVariant(currBuyer.getPostal_code());
    case NIP: return QVariant(currBuyer.getNIP());
    }

    // FIXME: Implement me!
    return QVariant();

}

QHash<int, QByteArray> BuyersRecListModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[LpRole] = "lp";
    names[buyerName] = "buyerName";
    names[adress] = "adress";
    names[town] = "town";
    names[postalCode] = "postalCode";
    names[NIP] = "nip";
    return names;
}

database *BuyersRecListModel::getmDatabase() const
{
    return mDatabase;
}

void BuyersRecListModel::setmDatabase(database *newDatabse)
{
    beginResetModel();
    if(mDatabase){
        mDatabase->disconnect(this);
    }
    mDatabase = newDatabse;

    if(mDatabase){
        connect(mDatabase, &database::preAddBuyer, this, [=](){
            const int  index = mDatabase->getCustomers().size();
            beginInsertRows(QModelIndex(), index,index);
        });
        connect(mDatabase, &database::postAddBuyer, this, [=](){
            endInsertRows();
        });
        connect(mDatabase, &database::preRemoveBuyer, this, [=](int index){
            beginRemoveRows(QModelIndex(), index,index);
        });
        connect(mDatabase, &database::postRemoveBuyer, this, [=](){
            endRemoveRows();
        });
    }
    endResetModel();
}
