#include "database.h"

bool database::getIsLoaded() const
{
    return isLoaded;
}

bool database::saveInvoicesRegister() const
{
    QFile mfile(InvoicesRegisterPath);

    if (!mfile.open(QIODevice::Truncate | QIODevice::WriteOnly))
    {
        qDebug() << "Unable to open invoices register";
        return false;
    }

    QTextStream outStream(&mfile);

    for(const auto & e:invoicesRegister){
        outStream << e.getSaleDate().toString(inputDateFormat) <<"\n"
                  << e.getBillingDate().toString(inputDateFormat)<<"\n"
                  <<e.getLastModificationDate().toString(inputDateFormat)<<"\n";

        seller mSeller = e.getSeller();

        outStream<<mSeller.getBussinessName()<<CSVSplitTag
                <<mSeller.getName()<<CSVSplitTag
               <<mSeller.getAdress()<<CSVSplitTag
              <<mSeller.getPostal_code()<<CSVSplitTag
             <<mSeller.getTown()<<CSVSplitTag
            <<mSeller.getNIP()<<CSVSplitTag
           <<mSeller.getPhoneNumber()<<CSVSplitTag
          <<mSeller.getAccountNumber()<<CSVSplitTag
         <<mSeller.getBankName()<<CSVSplitTag
        <<mSeller.getProducerNumber()<<CSVSplitTag<<"\n";

        customer mBuyer = e.getBuyer();

        outStream<<mBuyer.getName()<<CSVSplitTag
                <<mBuyer.getAdress()<<CSVSplitTag
               <<mBuyer.getPostal_code()<<CSVSplitTag
              <<mBuyer.getTown()<<CSVSplitTag
             <<mBuyer.getNIP()<<CSVSplitTag<<"\n";

        reciper mRecip = e.getRecip();

        if(mRecip.getName()!=""){
            outStream<<RecipertTag<<CSVSplitTag
                    <<mRecip.getName()<<CSVSplitTag
                   <<mRecip.getAdress()<<CSVSplitTag
                  <<mRecip.getPostal_code()<<CSVSplitTag
                 <<mRecip.getTown()<<CSVSplitTag<<"\n";
        }

        outStream<<e.getPaymentMethod()<<CSVSplitTag<<"\n";

        auto mRecords = e.getRecords();

        for(const auto & r: mRecords){
            outStream<<ProductTag <<CSVSplitTag<< r.getProductName() << CSVSplitTag
                    <<r.getRabat()<< CSVSplitTag
                   <<r.getPKWiU()<< CSVSplitTag
                  <<r.getQuantity()<< CSVSplitTag
                 <<r.getUnit()<< CSVSplitTag
                <<r.getPrice() << CSVSplitTag
               <<r.getTotalValue() << CSVSplitTag<<"\n";
        }

        outStream<<e.getPaymentDeadline().toString(inputDateFormat)<<"\n";
        outStream<< (e.getIsPaid() ? "TAK" : "NIE")<<"\n";
        outStream<<e.getInvoiceNumber()<<"\n";
    }
    mfile.close();

    return true;
}

const QString database::getLatestInvoiceNumber(){
    if(invoicesRegister.empty()){
        return "";
    }
    return invoicesRegister.last().getInvoiceNumber();
}

const QVector<customer> &database::getCustomers() const
{
    return customers;
}

const QVector<seller> &database::getSellers() const
{
    return sellers;
}

const QVector<product> &database::getProducts() const
{
    return products;
}

void database::addInvoiceToRegister(const invoiceBase &ai){

    oldInvoice oi;
    oi.setIsPaid(false);
    oi.setLastModificationDate(QDate::currentDate());
    oi.setRecords(ai.getRecords());
    oi.setSeller(ai.getSeller());
    oi.setBuyer(ai.getBuyer());
    oi.setRecip(ai.getRecip());
    oi.setPaymentMethod(ai.getPaymentMethod());
    oi.setBillingPalce(ai.getBillingPalce());
    oi.setSaleDate(ai.getSaleDate());
    oi.setBillingDate(ai.getBillingDate());
    oi.setPaymentDeadline(ai.getPaymentDeadline());
    oi.setInvoiceNumber(ai.getInvoiceNumber());
    invoicesRegister.push_back(oi);

}

database::database(QObject *parent)
    : QObject{parent}
{

    paymentMethods = invoicePaymentMethods;
    isLoaded =  loadCustomers() &&
            loadSellers() &&
            //loadPaymentMethods() &&
            loadProducts() &&
            loadInvoicesRegister();
}

bool database::loadCustomers(){

    QFile mfile(CustomersDatabasePath);
    QString tmp_text = "";
    QStringList tmp_vec;

    if (!mfile.open(QIODevice::ReadOnly))
    {
        qDebug() << "Unable to open customers database ";
        return false;
    }

    QTextStream inStream(&mfile);

    do
    {
        tmp_text = inStream.readLine();

        // ignore comments
        if (tmp_text[0] == CommentTag)
            continue;

        tmp_vec = tmp_text.split(CSVSplitTag);
        //reciper data
        if(tmp_text[0] == RecipertTag){
            //error in database, reciper without customer
            if(customers.empty()){
                return false;
            }
            //erase reciper tag
            tmp_vec.erase(tmp_vec.begin());

            reciper my_r(tmp_vec);
            customers.last().addReciper(my_r);
        }
        //customer data
        else{
            customer my_c(tmp_vec);
            customers.push_back(my_c);
        }

    } while (!inStream.atEnd());

    qDebug()<< "Succesfully loaded customers database";
    return true;
}

bool database::loadPaymentMethods()
{
    QFile mfile(PaymentMethodsPath);
    QString tmp_text = "";
    QStringList tmp_vec;

    if (!mfile.open(QIODevice::ReadOnly))
    {
        qDebug() << "Unable to open bussiness database";
        return false;
    }

    QTextStream inStream(&mfile);
    do
    {
        tmp_text = inStream.readLine();

        // ignore comments
        if (tmp_text[0] == CommentTag)
            continue;

        paymentMethods.push_back(tmp_text);

    } while (!inStream.atEnd());

    mfile.close();
    qDebug()<< "Succesfully loaded payment methods";
    return true;
}

bool database::loadProducts()
{
    QFile mfile(ProductsDatabasePath);
    QString tmp_text = "";
    QStringList tmp_vec;

    if (!mfile.open(QIODevice::ReadOnly))
    {
        qDebug() << "Unable to open products database ";
        return false;
    }

    QTextStream inStream(&mfile);

    do
    {
        tmp_text = inStream.readLine();

        // ignore comments
        if (tmp_text[0] == CommentTag)
            continue;

        tmp_vec = tmp_text.split(CSVSplitTag);

        product p(tmp_vec);
        if(p.getPolishName() != ""){
            products.push_back(p);
        }

    } while (!inStream.atEnd());

    qDebug()<< "Succesfully loaded products database";
    return true;
}

bool database::loadInvoicesRegister()
{
    QFile mfile(InvoicesRegisterPath);
    QString tmp_text = "";
    QStringList tmp_vec;
    oldInvoice oi;
    QDate tmp_date;

    if (!mfile.open(QIODevice::ReadOnly))
    {
        qDebug() << "Unable to open invoices register";
        return false;
    }

    QTextStream inStream(&mfile);
    int counter = 0;

    do{
        tmp_text = inStream.readLine();
        if(tmp_text.size()>0){
            if(tmp_text[0] == CommentTag) continue;
            else if(tmp_text[0] == RecipertTag){
                counter = 5;
            }
            else if(tmp_text[0] == ProductTag){
                counter = 7;
            }
        }
        else{
            counter = -1;
        }

        switch(counter){
        case  0:{
            tmp_text.replace(CSVSplitTag, "");
            oi.setSaleDate(tmp_date.fromString(tmp_text, inputDateFormat));
            counter = 1;
            break;
        }
        case 1:{
            tmp_text.replace(CSVSplitTag, "");
            oi.setBillingDate(tmp_date.fromString(tmp_text, inputDateFormat));
            counter = 2;
            break;
        }
        case 2:{
            tmp_text.replace(CSVSplitTag, "");
            oi.setLastModificationDate(tmp_date.fromString(tmp_text, inputDateFormat));
            counter = 3;
            break;
        }
        case 3:{
            tmp_vec = tmp_text.split(CSVSplitTag);
            seller s(tmp_vec);
            if(s.getName() != ""){
                oi.setSeller(s);
                counter = 4;
                break;
            }
            else {
                qDebug()<<"Error during invoices register loading a";
                return false;
            }
        }
        case 4:{
            tmp_vec = tmp_text.split(CSVSplitTag);
            customer my_c(tmp_vec);
            if(my_c.getName() != ""){
                oi.setBuyer(my_c);
                counter = 6;
                break;
            }
            else {
                qDebug()<<"Error during invoices register loading b";
                return false;
            }
        }
        case 5:{
            tmp_vec = tmp_text.split(CSVSplitTag);
            tmp_vec.erase(tmp_vec.begin());
            reciper my_r(tmp_vec);
            if(my_r.getName() != ""){
                oi.setRecip(my_r);
                counter = 6;
                break;
            }
            else {
                qDebug()<<"Error during invoices register loading c";
                return false;
            }
        }
        case 6:{
            tmp_text.replace(CSVSplitTag, "");
            oi.setPaymentMethod(tmp_text);
            counter = 8;
            break;
        }
        case 7:{
            tmp_vec = tmp_text.split(CSVSplitTag);
            tmp_vec.erase(tmp_vec.begin());
            InvoiceRecord p(tmp_vec);
            if(p.getProductName() != ""){
                oi.addRecord(p);
                counter = 8;
                break;
            }
            else{
                qDebug()<<"Error during invoices register loading d";
                return false;
            }
        }
        case 8:{
            tmp_text.replace(CSVSplitTag, "");
            oi.setPaymentDeadline(tmp_date.fromString(tmp_text, inputDateFormat));
            counter = 9;
            break;
        }
        case 9:{
            tmp_text.replace(CSVSplitTag, "");
            bool isPaid = tmp_text == "TAK";
            oi.setIsPaid(isPaid);
            counter = 10;
            break;
        }
        case 10:{
            tmp_text.replace(CSVSplitTag, "");
            oi.setInvoiceNumber(tmp_text);
            invoicesRegister.push_back(oi);
            oldInvoice oi_new;
            oi = oi_new;
            counter = 0;
            break;
        }
        }

        if(inStream.atEnd()) counter = -1;

    }while(counter != -1);

//    qDebug()<<"Succesfully loaded invoices register.";
//    if(!invoicesRegister.empty())
//    qDebug()<<"Invoices count: " << invoicesRegister.size();

    mfile.close();

    return true;
    /*
 Data sprzedaży
Data wystawienia
Data ostatniej modyfikacji
Sprzedawca
Nabywca
Odbiorca
Rodzaj płatności
Nazwa towaru Ilość j.m. Cena Rabat PKWiU
Termin płatności
Czy zapłacono?
Nr rachunku
*/
}

bool database::loadSellers()
{
    QFile mfile(SellersDatabasePath);
    QString tmp_text = "";
    QStringList tmp_vec;

    if (!mfile.open(QIODevice::ReadOnly))
    {
        qDebug() << "Unable to open bussiness database";
        return false;
    }

    QTextStream inStream(&mfile);

    do
    {
        tmp_text = inStream.readLine();

        // ignore comments
        if (tmp_text[0] == CommentTag)
            continue;

        tmp_vec = tmp_text.split(CSVSplitTag);

        if(tmp_vec.size() == sellerElementsCount){
            seller s(tmp_vec)   ;
            sellers.push_back(s);
        }

    } while (!inStream.atEnd());

    mfile.close();
    qDebug()<< "Succesfully loaded sellers database";
    return true;
}

const QStringList database::getCustomersNames() const {
    QStringList l;
    for(const auto & c: customers){
        l.push_back(c.getName());
    }
    return l;
}

const QStringList database::getRecipersNames(const QString &custName){
    QStringList a;
    for(const auto & c: customers){
        if(c.getName() == custName){
            return c.getRecipersNames();
        }
    }
    return a;//return empty list if customer is not found
}

const QStringList database::getSellersNames() const{
    QStringList s;
    for(const auto & e: sellers){
        s.push_back(e.getName());
    }
    return s;
}

const QStringList database::getProductsPolishNames() const
{
    QStringList a;
    for(const auto & p: products){
        a.push_back(p.getPolishName()+" "+p.getSpecies());
    }
    return a;
}

const QStringList database::getPaymentMethods() const{
    return paymentMethods;
}


