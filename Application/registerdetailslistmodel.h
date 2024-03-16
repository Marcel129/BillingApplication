#ifndef REGISTERDETAILSLISTMODEL_H
#define REGISTERDETAILSLISTMODEL_H

#include <QAbstractListModel>
#include "database.h"
class database;

class registerDetailsListModel: public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(database *mDatabase READ getmDatabase WRITE setmDatabase);
public:
    explicit registerDetailsListModel(QObject *parent = nullptr);

    enum{
        LpRole = Qt::UserRole,
        plantPolishName,
        plantsAmmount,
        plantsPrice,
        plantsRabat
    };

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    virtual QHash<int, QByteArray> roleNames( ) const override;

    database * getmDatabase()const;
    void setmDatabase(class database *newDatabse);

private:
    database * mDatabase;
    int currInvoiceIndex;
};

#endif // REGISTERDETAILSLISTMODEL_H
