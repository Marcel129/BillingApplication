#include "database.h"

bool database::getIsLoaded() const
{
    return isLoaded;
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

database::database(QObject *parent)
    : QObject{parent}
{
    isLoaded =  loadCustomers() &&
            loadSellers() &&
            loadPaymentMethods() &&
            loadProducts();
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
        a.push_back(p.getPolishName());
    }
    return a;
}

const QStringList database::getPaymentMethods() const{
    return paymentMethods;
}


