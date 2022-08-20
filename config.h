#ifndef CONFIG_H
#define CONFIG_H

#include <QString>
#include <QStringList>

const QString resourcesPath("D:\\SzkolkaRoslinOpatow\\Aplikacja\\External_resources\\");
const QString FVpath("D:\\SzkolkaRoslinOpatow\\Aplikacja\\");
const QString SelleresTag("!Metody platnosci");

//database files tags
const char CommentTag = '#';
const char RecipertTag = '!';
const char CSVSplitTag = ';';
const char ProductTag = '@';

const QString CustomersDatabasePath = resourcesPath + "Customers_database.csv";
const QString SellersDatabasePath = resourcesPath + "Sellers_database.csv";
const QString ProductsDatabasePath = resourcesPath + "Plants_database.csv";
const QString PaymentMethodsPath = resourcesPath + "Payment_methods.csv";
const QString InvoicesRegisterPath = resourcesPath + "Invoices_register.csv";

const QString outputDateFormat("d MMMM yyyy");
const QString inputDateFormat("d.M.yyyy");

const QString defaultBillingPlace = "Opatów";
const QString defaultInvoiceNumber = "1/1/2000";

static void removePolishDiacritics(QString & str){
    QStringList diacritics = {"ą",	"ę",	"ć",	"ł",	"ń",	"ó",	"ś",	"ż",	"ź",	"Ą",	"Ę",	"Ć",	"Ł",	"Ń",	"Ó",	"Ś",	"Ż",	"Ź"};
    QStringList normal = {"a",	"e",	"c",	"l",	"n",	"o",	"s",	"z",	"z",	"A",	"E",	"C",	"L",	"N",	"O",	"S",	"Z",	"Z"};

    if(str != ""){
        for(int i=0; i<diacritics.size();i++){
            str.replace(diacritics[i], normal[i]);
        }
    }
}
#endif // CONFIG_H
