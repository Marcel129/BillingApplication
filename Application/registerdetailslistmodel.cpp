#include "registerdetailslistmodel.h"

registerDetailsListModel::registerDetailsListModel(QObject *parent)
    : QAbstractListModel(parent), mDatabase(nullptr)
{
    currInvoiceIndex = 0;
}


int registerDetailsListModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid() || !mDatabase)
        return 0;

    return mDatabase->getReversedInvoicesRegister().at(currInvoiceIndex).getRecords().size();
    // FIXME: Implement me!
}

QVariant registerDetailsListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !mDatabase)
        return QVariant();
//qDebug()<<"Biezacy index: "<<currInvoiceIndex<<"\n";
    const InvoiceRecord currRecord = mDatabase->getReversedInvoicesRegister().at(currInvoiceIndex).getRecords().at(index.row());
    switch(role){
    case LpRole: return QVariant(QString::number(index.row()));
    case plantPolishName: return QVariant(currRecord.getProductName());
    case plantsAmmount: return QVariant(currRecord.getQuantity());
    case plantsPrice: return QVariant(currRecord.getPrice());
    case plantsRabat: return QVariant(currRecord.getRabat());
    }

    // FIXME: Implement me!
    return QVariant();
}

QHash<int, QByteArray> registerDetailsListModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[LpRole] = "lp";
    names[plantPolishName] = "plantPolishName";
    names[plantsAmmount] = "plantsAmmount";
    names[plantsPrice] = "plantsPrice";
    names[plantsRabat] = "plantsRabat";
    return names;
}

database *registerDetailsListModel::getmDatabase() const
{
    return mDatabase;
}

void registerDetailsListModel::setmDatabase(database *newDatabse)
{
    beginResetModel();
    if(mDatabase){
        mDatabase->disconnect(this);
    }
    mDatabase = newDatabse;

    if(mDatabase){
        connect(mDatabase, &database::refreshInvoiceRecordsInRegisterTableViewSignal, this, [=](int index){
            currInvoiceIndex = index;
            qDebug()<<"Current index: "<<index;
             beginResetModel();
             endResetModel();
        });
    }
    endResetModel();
}

