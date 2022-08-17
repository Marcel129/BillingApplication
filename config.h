#ifndef CONFIG_H
#define CONFIG_H

#include <QString>

const QString resourcesPath("D:\\SzkolkaRoslinOpatow\\Aplikacja\\External_resources\\");
const QString FVpath("D:\\SzkolkaRoslinOpatow\\Aplikacja\\");
const QString SelleresTag("!Metody platnosci");

//database files tags
const char CommentTag = '#';
const char RecipertTag = '!';
const char CSVSplitTag = ';';

const QString CustomersDatabasePath = resourcesPath + "Customers_database.csv";
const QString SellersDatabasePath = resourcesPath + "Sellers_database.csv";
const QString PaymentMethodsPath = resourcesPath + "Payment_methods.csv";

const QString outputDateFormat("d MMMM yyyy");
const QString inputDateFormat("d.M.yyyy");

const QString defaultBillingPlace = "Opatów";
#endif // CONFIG_H
