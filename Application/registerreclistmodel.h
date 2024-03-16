#ifndef REGISTERRECLISTMODEL_H
#define REGISTERRECLISTMODEL_H

#include <QAbstractListModel>
#include "database.h"
#include "config.h"

class database;

class RegisterRecListModel: public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(database *mDatabase READ getmDatabase WRITE setmDatabase)

public:
    explicit RegisterRecListModel(QObject *parent = nullptr);

    enum{
        LpRole = Qt::UserRole,
        invoiceNumber,
        buyer,
        peymentMethod,
        date
    };

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    virtual QHash<int, QByteArray> roleNames( ) const override;

    database * getmDatabase()const;
    void setmDatabase(class database *newDatabse);

private:
    database * mDatabase;
};

#endif // REGISTERRECLISTMODEL_H
