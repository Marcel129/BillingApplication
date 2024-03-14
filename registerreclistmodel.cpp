#include "registerreclistmodel.h"

RegisterRecListModel::RegisterRecListModel(QObject *parent)
    : QAbstractListModel(parent), mDatabase(nullptr)
{
}

int RegisterRecListModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid() || !mDatabase)
        return 0;

    return mDatabase->getInvoicesRegister().size();
    // FIXME: Implement me!
}

QVariant RegisterRecListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !mDatabase)
        return QVariant();

    const oldInvoice currIvoice = mDatabase->getReversedInvoicesRegister().at(index.row());
    switch(role){
    case LpRole: return QVariant(QString::number(index.row()));
    case invoiceNumber: return QVariant(currIvoice.getInvoiceNumber());
    case buyer: return QVariant(currIvoice.getBuyer().getName());
    case peymantMethod: return QVariant(currIvoice.getPaymentMethod());
    case date: return QVariant(currIvoice.getSaleDate().toString(invoicesSavingFolderPath));
    }

    // FIXME: Implement me!
    return QVariant();
}

QHash<int, QByteArray> RegisterRecListModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[LpRole] = "lp";
    names[invoiceNumber] = "invoiceNumber";
    names[buyer] = "buyer";
    names[peymantMethod] = "peymantMethod";
    names[date] = "date";
    return names;
}

database *RegisterRecListModel::getmDatabase() const
{
    return mDatabase;
}

void RegisterRecListModel::setmDatabase(database *newDatabse)
{
    beginResetModel();
    if(mDatabase){
        mDatabase->disconnect(this);
    }
    mDatabase = newDatabse;

    if(mDatabase){
        connect(mDatabase, &database::preRemoveInvoice, this, [=](int index){
            beginRemoveRows(QModelIndex(), index,index);
        });
        connect(mDatabase, &database::postRemoveInvoice, this, [=](){
            endRemoveRows();
        });
    }
    endResetModel();
}
