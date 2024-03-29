#ifndef BUYERSRECLISTMODEL_H
#define BUYERSRECLISTMODEL_H

#include <QAbstractListModel>
#include "database.h"

class database;

class BuyersRecListModel: public QAbstractListModel
{    Q_OBJECT
     Q_PROPERTY(database *mDatabase READ getmDatabase WRITE setmDatabase)

 public:
     explicit BuyersRecListModel(QObject *parent = nullptr);

     enum{
         LpRole = Qt::UserRole,
         buyerName,
         adress,
         town,
         postalCode,
         NIP
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

#endif // BUYERSRECLISTMODEL_H
