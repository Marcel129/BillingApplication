#include "invoicetemplate.h"

InvoiceTemplate::InvoiceTemplate(QObject *parent)
    : QObject{parent}
{

}

QString InvoiceTemplate::getPart(FVTemplatePart a)
{
    return parts.at(a);
};

QStringList & InvoiceTemplate::getAllParts(){
    return parts;
}


bool InvoiceTemplate::load()
{
    QFile mfile(resourcesFolderPath + FVLTemplateDefaultFileName);
    QString invoicesFolderPath("");


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

void InvoiceTemplate::insertValuesIntoKeywords(
        seller Seller,
        customer buyer,
        reciper recip,
        QString paymentMethod,
        QString billingPalce,
        QDate billingDate,
        QDate saleDate,
        QDate paymentDeadline,
        QString invoiceNumber,
        double totalSum){

    for(QString & s: parts){
        s.replace(invoicesSavingFolderPath, Seller.getBussinessName());
        s.replace(invoicesSavingFolderPath,Seller.getAdress());
        s.replace(invoicesSavingFolderPath, Seller.getPostal_code() + " "+Seller.getTown());
        s.replace(invoicesSavingFolderPath, Seller.getTown());
        s.replace(invoicesSavingFolderPath, Seller.getName());
        s.replace(invoicesSavingFolderPath, Seller.getProducerNumber());
        s.replace(invoicesSavingFolderPath, saleDate.toString(outputDateFormat));
        s.replace(invoicesSavingFolderPath, billingDate.toString(outputDateFormat));
        s.replace(invoicesSavingFolderPath, billingPalce);
        s.replace(invoicesSavingFolderPath, Seller.getPhoneNumber());
        s.replace(invoicesSavingFolderPath, buyer.getName());
        s.replace(invoicesSavingFolderPath, buyer.getAdress());
        s.replace(invoicesSavingFolderPath, buyer.getPostal_code() +" "+ buyer.getTown());
        s.replace(invoicesSavingFolderPath, buyer.getNIP());
        s.replace(invoicesSavingFolderPath,recip.getName());
        s.replace(invoicesSavingFolderPath,recip.getAdress());
        s.replace(invoicesSavingFolderPath, recip.getPostal_code() +" "+ recip.getTown());
        s.replace(invoicesSavingFolderPath,invoiceNumber);
        s.replace(invoicesSavingFolderPath, numberInWords_polish(totalSum));
        s.replace(invoicesSavingFolderPath, QString::number(totalSum, 'd',2)+" zł");
        s.replace(invoicesSavingFolderPath,paymentMethod);
        s.replace(invoicesSavingFolderPath, paymentDeadline.toString(inputDateFormat));
        s.replace(invoicesSavingFolderPath,Seller.getAccountNumber());
    }
}

void InvoiceTemplate::refresh(){
    parts = sourceParts;
};

