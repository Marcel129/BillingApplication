#ifndef RECIPERRECLISTMODEL_H
#define RECIPERRECLISTMODEL_H

#include <QAbstractListModel>
#include "database.h"
class database;

class ReciperRecListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(database *mDatabase READ getmDatabase WRITE setmDatabase)

public:
    explicit ReciperRecListModel(QObject *parent = nullptr);

    enum{
        LpRole = Qt::UserRole,
        reciperName,
        address,
        postalCode,
        town
    };

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    virtual QHash<int, QByteArray> roleNames( ) const override;

    database * getmDatabase()const;
    void setmDatabase(class database *newDatabse);

private:
    database * mDatabase;
    int actCustomerIndex;
};

#endif // RECIPERRECLISTMODEL_H
