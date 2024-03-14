#ifndef CONFIG_H
#define CONFIG_H

//libs
#include <QDebug>
#include <QFile>
#include <QVector>
#include <QString>
#include <QStringList>
#include <QObject>
#include <QMessageBox>
#include <QDate>
#include <QDir>
#include <QSharedPointer>

#define DEV_MODE

#ifdef DEV_MODE
const QString resourcesPath("D:\\SzkolkaRoslinOpatow\\Application_deployment\\External_resources\\");
const QString invoicesPath("D:\\SzkolkaRoslinOpatow\\Aplikacja\\");
#endif

#ifndef DEV_MODE
const QString resourcesPath("D:\\Aplikacja_szkolka\\External_resources\\");
const QString invoicesPath("D:\\Szkolka_rachunki\\");
#endif

//database files tags
const char CommentTag = '#';
const char RecipertTag = '!';
const char CSVSplitTag = ';';
const char ProductTag = '@';
const QString SelleresTag("!Metody platnosci");

const QString CustomersDatabasePath = resourcesPath + "Customers_database.csv";
const QString SellersDatabasePath = resourcesPath + "Sellers_database.csv";
const QString ProductsDatabasePath = resourcesPath + "Plants_database.csv";
const QString PaymentMethodsPath = resourcesPath + "Payment_methods.csv";
const QString InvoicesRegisterPath = resourcesPath + "Invoices_register.csv";

const QString outputDateFormat("d MMMM yyyy");
const QString inputDateFormat("d.M.yyyy");

const QString defaultBillingPlace = "Opatów";
const QString defaultInvoiceNumber = "1/1/2000";
const QStringList invoicePaymentMethods = {"przelew 7 dni",
                                           "przelew 14 dni",
                                           "przelew 21 dni",
                                           "zapłacono gotówką"};

static void removePolishDiacritics(QString & str){
    QStringList diacritics = {"ą",	"ę",	"ć",	"ł",	"ń",	"ó",	"ś",	"ż",	"ź",	"Ą",	"Ę",	"Ć",	"Ł",	"Ń",	"Ó",	"Ś",	"Ż",	"Ź"};
    QStringList normal = {"a",	"e",	"c",	"l",	"n",	"o",	"s",	"z",	"z",	"A",	"E",	"C",	"L",	"N",	"O",	"S",	"Z",	"Z"};

    if(str != ""){
        for(int i=0; i<diacritics.size();i++){
            str.replace(diacritics[i], normal[i]);
        }
    }
}

static QString trojka(int t){
    QString mTrojka;

    QStringList jednosci = {
        "zero",
        "jeden",
        "dwa",
        "trzy",
        "cztery",
        "pięć",
        "sześć",
        "siedem",
        "osiem",
        "dziewięć",
        "dziesięć",
        "jedenaście",
        "dwanaście",
        "trzynaście",
        "czternaście",
        "piętnaście",
        "szesnaście",
        "siedemnaście",
        "osiemnaście",
        "dziewiętnaście"
    };

    QStringList dziesiatki = {
        "zero",
        "dziesięć",
        "dwadzieścia",
        "trzydzieści",
        "czterdzieści",
        "pięćdziesiąt",
        "sześćdziesiąt",
        "siedemdziesiąt",
        "osiemdziesiąt",
        "dziewięćdziesiąt"
    };

    QStringList setki = {
        "zero",
        "sto",
        "dwieście",
        "trzysta",
        "czterysta",
        "pięćset",
        "sześćset",
        "siedemset",
        "osiemset",
        "dziewięćset"
    };

    if(t<=19){
        mTrojka = jednosci[t];
    }
    else if(t>19 && t<100){
        if(t%10){
            mTrojka = dziesiatki[(int)(t/10)] + " " + jednosci[t%10];
        }
        else{
            mTrojka = dziesiatki[(int)(t/10)];
        }
    }
    else if(t>=100 && t<1000){
        if(t%100){
            mTrojka = setki[(int)t/100]+" "+trojka(t%100);
        }
        else{
            mTrojka = setki[(int)t/100];
        }
    }

    return mTrojka;
}

static QString rzadWielkosci(int t, char type){
    t = t%100;

    if(type == 'z'){
        if(t == 0 || (t>=5 && t<=19)) return "złotych";
        else if(t==1)return "złoty";
        else if(t>=2 && t<=4) return "złote";
        else if(t>=20){
            t=t%10;
            if(t ==0 || t==1 || t>=5)return "złotych";
            else if(t>=2 && t<=4)return "złote";
        }
        else return "Cannot convert number";
    }
    else if(type == 'g'){
        if(t == 0 || (t>=5 && t<=19)) return "groszy";
        else if(t==1)return "grosz";
        else if(t>=2 && t<=4) return "grosze";
        else if(t>=20){
            t=t%10;
            if(t ==0 || t==1 || t>=5)return "groszy";
            else if(t>=2 && t<=4)return "grosze";
        }
        else return "Cannot convert number";
    }
    else if(type == 't'){
        if(t == 0 || (t>=5 && t<=19)) return "tysięcy";
        else if(t==1)return "tysiąc";
        else if(t>=2 && t<=4) return "tysiące";
        else if(t>=20){
            t=t%10;
            if(t ==0 || t==1 || t>=5)return "tysięcy";
            else if(t>=2 && t<=4)return "tysiące";
        }
        else return "Cannot convert number";
    }
    else{
        return "Cannot convert number";
    }
}

static QString numberInWords_polish(double num){
    double maxNumber = 999999;
    long int zloteInt, groszeInt;
    QString zlote, grosze, mnum, zloteResult, groszeResult;
    if(num > maxNumber){
        return "Number is too big to convert";
    }
    if(num < 0) num = -num;

    mnum = QString::number(num,'d',2);

    QStringList q = mnum.split(".");
    if(q.size() == 2){
        zlote = q[0];
        grosze = q[1];
    }
    else{
        zlote = mnum;
    }

    groszeInt = grosze.toInt();
    if(grosze.size() >=1 && grosze.size()<=2){
        grosze = trojka(groszeInt) + " " + rzadWielkosci(groszeInt, 'g');
    }

    zloteInt = zlote.toLong();
    if(zlote.size() >=1 && zlote.size()<=3){
        zlote = trojka(zloteInt)+ " "+ rzadWielkosci(zloteInt,'z');
    }
    else if(zlote.size() >=4 && zlote.size()<=6){
        zlote = trojka(zloteInt/1000)+ " "+ rzadWielkosci(zloteInt/1000,'t')+
                " "+trojka(zloteInt%1000)+ " "+ rzadWielkosci(zloteInt%1000,'z');
    }
    return zlote + " " + grosze;

}


#endif // CONFIG_H
