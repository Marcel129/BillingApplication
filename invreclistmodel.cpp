#include "invreclistmodel.h"
#include<invoice.h>

InvRecListModel::InvRecListModel(QObject *parent)
    : QAbstractListModel(parent), mInvoice(nullptr)
{
}

int InvRecListModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid() || !mInvoice)
        return 0;

    return mInvoice->getRecords().size();
}

QVariant InvRecListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !mInvoice)
        return QVariant();

    const InvoiceRecord currRec = mInvoice->getRecords().at(index.row());
    switch(role){
    case LpRole: return QVariant(QStringLiteral("nr"));
    case NameRole: return QVariant(currRec.getProductName());
    case AmmountRole: return QVariant(QString::number(currRec.getQuantity(), 'd', 0));
    case PriceRole: return QVariant(QString::number(currRec.getPrice(),'d', 2));
    case RabatRole: return QVariant(QString::number(currRec.getRabat(),'d', 1));
    }

    return QVariant();
}

QHash<int, QByteArray> InvRecListModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[LpRole] = "lp";
    names[NameRole] = "name";
    names[AmmountRole] = "ammount";
    names[PriceRole] = "price";
    names[RabatRole] = "rabat";
    return names;
}

invoice *InvRecListModel::getmInvoice() const
{
    return mInvoice;
}

void InvRecListModel::setmInvoice(class invoice *newInvoice)
{
    beginResetModel();
    if(mInvoice){
        mInvoice->disconnect(this);
    }
    mInvoice = newInvoice;

    if(mInvoice){
        connect(mInvoice, &invoice::preInvAddRecord, this, [=](){
            const int  index = mInvoice->getRecords().size();
            beginInsertRows(QModelIndex(), index,index);
        });
        connect(mInvoice, &invoice::postInvAddRecord, this, [=](){
            endInsertRows();
        });
        connect(mInvoice, &invoice::preInvRemoveRecord, this, [=](int index){
            beginRemoveRows(QModelIndex(), index,index);
        });
        connect(mInvoice, &invoice::postInvRemoveRecord, this, [=](){
            endRemoveRows();
        });
    }
    endResetModel();
}
