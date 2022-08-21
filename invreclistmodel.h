#ifndef INVRECLISTMODEL_H
#define INVRECLISTMODEL_H

#include <QAbstractListModel>
#include<invoice.h>
class invoice;

class InvRecListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(invoice *mInvoice READ getmInvoice WRITE setmInvoice)

public:
    explicit InvRecListModel(QObject *parent = nullptr);

    enum{
        LpRole = Qt::UserRole,
        NameRole,
        AmmountRole,
        PriceRole,
        RabatRole
    };

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    virtual QHash<int, QByteArray> roleNames( ) const override;

    invoice *getmInvoice() const;
    void setmInvoice(class invoice *newInvoice);

private:
    invoice * mInvoice;
};

#endif // INVRECLISTMODEL_H
