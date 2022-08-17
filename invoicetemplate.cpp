#include "invoicetemplate.h"

FVTemplate::FVTemplate(QObject *parent)
    : QObject{parent}
{

}

QString FVTemplate::getPart(FVTemplatePart a)
{
    return parts.at(a);
};

QStringList & FVTemplate::getAllParts(){
    return parts;
}


bool FVTemplate::load()
{
    QFile mfile(resourcesPath + FVLTemplateDefaultFileName);
    QString tmp_text("");


    if (!mfile.open(QIODevice::ReadOnly))
    {
        qDebug() << "Unable to open template file";
        return false;
    }

    QTextStream inStream(&mfile);
    inStream.setCodec("UTF-8");

    unsigned int index = 0;

    do
    {
        tmp_text = "";
        parts.push_back(tmp_text);
        do
        {
            tmp_text = inStream.readLine();

            if (tmp_text != spacer && tmp_text != EOFString)
            {
                parts[index] += (tmp_text + "\n");
            }
        } while (tmp_text != spacer && tmp_text != EOFString);

        index++;
    } while (tmp_text != EOFString);

    mfile.close();

    is_loaded = (Ending == (index-1));
    if(is_loaded){
        qDebug()<<"Invoice template loaded sucesfully";
    }

    sourceParts = parts;

    return is_loaded;
}

void FVTemplate::insertValuesIntoKeywords(
        seller Seller,
        customer buyer,
        reciper recip,
        QString paymentMethod,
        QString billingPalce,
        QDate billingDate,
        QDate saleDate,
        QString paymentDeadline){

    for(QString & s: parts){
        s.replace("KEYWORD-SELLER-BUSSINES-FULL-NAME", Seller.getBussinessName());
        s.replace("KEYWORD-SELLER-ADRESS-1",Seller.getAdress());
        s.replace("KEYWORD-SELLER-ADRESS-2", Seller.getPostal_code());
        s.replace("KEYWORD-SELLER-BUSSINES-TOWN", Seller.getTown());
        s.replace("KEYWORD-SELLER-NAME", Seller.getName());
        s.replace("KEYWORD-PRODUCER-NUMBER", Seller.getProducerNumber());
        s.replace("KEYWORD-SELLING-DATE", saleDate.toString(outputDateFormat));
        s.replace("KEYWORD-BILLING-DATE", billingDate.toString(outputDateFormat));
        s.replace("KEYWORD-BILLING-TOWN", billingPalce);
        s.replace("KEYWORD-SELLER-PHONE-NUMBERS", Seller.getPhoneNumber());
        s.replace("KEYWORD-BUYER-BUSSINES-FULL-NAME", buyer.getName());
        s.replace("KEYWORD-BUYER-ADRESS-1", buyer.getAdress());
        s.replace("KEYWORD-BUYER-ADRESS-2", buyer.getPostal_code() +" "+ buyer.getTown());
        s.replace("KEYWORD-BUYER-NIP", buyer.getNIP());
        s.replace("KEYWORD-RECIPIENT-FULL-NAME",recip.getName());
        s.replace("KEYWORD-RECIPER-ADRESS-1",recip.getAdress());
        s.replace("KEYWORD-RECIPER-ADRESS-2", recip.getPostal_code() +" "+ recip.getTown());
        //            s.replace("KEYWORD-INVOICE-NUMBER");
        //            s.replace("KEYWORD-TOTAL-TO-PAY");
        //            s.replace("KEYWORD-TOTAL-TO-PAY-IN-WORDS");
        s.replace("KEYWORD-PAYMENT-METHOD",paymentMethod);
        //            s.replace("KEYWORD-PAYMENT-DATE");
        s.replace("KEYWORD-SELLER-ACCOUNT-NUMBER",Seller.getAccountNumber());
    }
}

void FVTemplate::refresh(){
    parts = sourceParts;
};

