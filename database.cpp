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

bool database::saveCustomers() const
{
    QFile mfile(CustomersDatabasePath);

    if (!mfile.open(QIODevice::Truncate | QIODevice::WriteOnly))
    {
        qDebug() << "Unable to open customers register";
        return false;
    }

    QTextStream outStream(&mfile);

    outStream<<"#Wykrzyknikami oznaczeni są odbiorcy przypisani do nabywców bezpośrednio nad nimi"<<"\n"<<
               "#Odbiorca;	adres;	miasto	;kod_pocztowy;	nip/kod pocztowy"<<"\n";

    for(const auto & mBuyer:customers){
        outStream<<mBuyer.getName()<<CSVSplitTag
                <<mBuyer.getAdress()<<CSVSplitTag
               <<mBuyer.getPostal_code()<<CSVSplitTag
              <<mBuyer.getTown()<<CSVSplitTag
             <<mBuyer.getNIP()<<CSVSplitTag<<"\n";
        for(const auto & mRecip: mBuyer.getRecipers()){
            outStream<<RecipertTag<<CSVSplitTag
                    <<mRecip.getName()<<CSVSplitTag
                   <<mRecip.getAdress()<<CSVSplitTag
                  <<mRecip.getPostal_code()<<CSVSplitTag
                 <<mRecip.getTown()<<CSVSplitTag
                <<"\n";
        }
    }

    mfile.close();

    return true;
}

bool database::saveSellers() const
{
    QFile mfile(SellersDatabasePath);

    if (!mfile.open(QIODevice::Truncate | QIODevice::WriteOnly))
    {
        qDebug() << "Unable to open sellers register";
        return false;
    }

    QTextStream outStream(&mfile);

    outStream<<"#NazwaWystawcaAdresMiastoKodpocztowyNIPTelefonNumerrachunkuBankNrproducent\n";

    for(const auto & mSeller: sellers){
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
    }

    mfile.close();

    return true;
}

bool database::saveProducts() const
{
    QFile mfile(ProductsDatabasePath);

    if (!mfile.open(QIODevice::Truncate | QIODevice::WriteOnly))
    {
        qDebug() << "Unable to open products register";
        return false;
    }

    QTextStream outStream(&mfile);

    outStream<<"#Rodzaj;	nazwa łacińska;	nazwa polska;	gatunek;	numer ewidencyjny\n";

    for(const auto & mProduct: products){
        outStream<<mProduct.getType()<< CSVSplitTag
                <<mProduct.getLatinName()<< CSVSplitTag
               <<mProduct.getPolishName()<< CSVSplitTag
              <<mProduct.getSpecies()<< CSVSplitTag
             <<mProduct.getRegisterNumber()<< CSVSplitTag<<"\n";
    }

    mfile.close();

    return true;
}

void database::pushDatabaseToRemoteRepository() const
{
#ifdef PUSH_DATABASE_TO_REPOSITORY
    system("git add External_resources/Customers_database.csv"
           "External_resources/Invoices_register.csv"
           "External_resources/Payment_methods.csv"
           "External_resources/Plants_database.csv"
           "External_resources/Sellers_database.csv");
    system("git commit -m\"Saving database on close the program \"");
    system("git push --set-upstream https://github.com/Marcel129/SmallBA_Deployment main");
#endif
}

void database::addCustomer(const QString &n, const QString &a, const QString &t, const QString &pc, const QString &NIP)
{
    emit preAddBuyer(customers.size());
    customer c;
    c.setName(n);
    c.setAdress(a);
    c.setPostal_code(pc);
    c.setTown(t);
    c.setNIP(NIP);
    customers.push_back(c);
    emit postAddBuyer();
}

void database::addReciper(const QString &cust, const QString &n, const QString &a, const QString &t, const QString &pc)
{
    emit preAddReciper(cust.size());
    reciper r;
    r.setName(n);
    r.setAdress(a);
    r.setPostal_code(pc);
    r.setTown(t);

    for(auto & c: customers){
        if(c.getName() == cust){
            c.addReciper(r);
            emit postAddReciper();
            return;
        }
    }
}

const QStringList database::getProductsTypes() const
{
    return mProductsTypes;
}

const QStringList database::getProductsTypesShorts() const
{
    return mPoductsTypesShorts;
}

const QString database::getCustomerName(int index)
{
    if(index>=0 && index<customers.size()){
        return customers.at(index).getName();
    }
    return "";
}

void database::addProduct(const QString &type,
                          const QString &latinName,
                          const QString &polishName,
                          const QString &species,
                          const QString &registerNumber)
{
    if(latinName == "" || polishName == ""|| species == ""){
        QMessageBox msgBox;
        msgBox.setText("The document has been modified.");
        msgBox.exec();
        return;
    }

    product p;
    p.setType(type);
    p.setLatinName(latinName);
    p.setPolishName(polishName);
    p.setSpecies(species);
    if(registerNumber == ""){
        QString s, nRegNum = "";
        int biggest = 0, actuall = 0;

        for(const auto & e: products){
            if(e.getType() == type){
                try{
                    actuall = e.getRegisterNumber().split('/').last().toInt();
                }
                catch(...){
                    qDebug()<<"Problem occurs during calculating new product's evidence number";
                }
                if(actuall > biggest) biggest = actuall;
            }
        }
        if(type == productsTypes[0]) s = productsTypesShorts[0];
        else if(type == productsTypes[1]) s = productsTypesShorts[1];
        else if(type == productsTypes[2]) s = productsTypesShorts[2];
        else{
            qDebug()<<"Unknown product type";
            s = "ERROR";
        }
        p.setRegisterNumber( s + "/" + QString::number(biggest));
        qDebug()<<"New number is: " << p.getRegisterNumber();
    }
    products.push_back(p);
}

bool database::removeProductAt(int index){
    emit preRemoveProduct(index);

    if(index >=0 && index <products.size()){
        products.erase(products.begin()+index);
        emit postRemoveProduct();
        return true;
    }
    emit postRemoveProduct();
    return false;
}

bool database::removeCustomerAt(int index)
{
    emit preRemoveBuyer(index);
    int i=0, recipersCount = customers.at(index).getRecipers().size();

    while(i<recipersCount){
        emit preRemoveReciper(i);
        i++;
    }
    i=0;

    if(index >=0 && index < customers.size()){
        customers.erase(customers.begin()+index);
        while(i<recipersCount){
            emit postRemoveReciper();
            i++;
        }
        emit postRemoveBuyer();
        return true;
    }
    while(i<recipersCount){
        emit postRemoveReciper();
        i++;
    }
    emit postRemoveBuyer();
    return false;
}

bool database::removeInvoiceAt(int index)
{
    emit preRemoveInvoice(index);

    if(index >=0 && index < invoicesRegister.size()){
        invoicesRegister.erase(invoicesRegister.begin()+index);
        emit postRemoveInvoice();
        return true;
    }
    emit postRemoveInvoice();
    return false;
}

bool database::removeInvoiceFromReversedRegisterAt(int index)
{
    emit preRemoveInvoice(index);

    if(index >=0 && index < invoicesRegister.size()){
        invoicesRegister.erase(invoicesRegister.end()-index-1);
        emit postRemoveInvoice();
        return true;
    }
    emit postRemoveInvoice();
    return false;
}


bool database::removeReciperAt(int cIndex, int rIndex)
{
    emit preRemoveReciper(rIndex);
    if(cIndex >=0 && cIndex < customers.size()){
        if(rIndex >=0 && rIndex < customers[cIndex].getRecipers().size()){
            customers[cIndex].removeReciper(customers[cIndex].getRecipers()[rIndex]);
            emit postRemoveReciper();
            return true;
        }
        emit postRemoveReciper();
        return false;
    }
    emit postRemoveReciper();
    return false;
}

void database::refreshRecipersTableView(int index)
{
    emit refreshRecipersTableViewSignal(index);
//    int i=0, recipersCount = this->customers.at(rowsCount).getRecipers().size();

//    while(i<recipersCount){
//        emit preRemoveReciper(0);
//        emit postRemoveReciper();
//        i++;
//    }
//    i=0;

//    while(i<recipersCount){
//        emit preAddReciper(i);
//        emit postAddReciper();
//        i++;
//    }
//    i=0;


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

const QVector<oldInvoice> &database::getInvoicesRegister() const
{
    return invoicesRegister;
}

const QVector<oldInvoice> database::getReversedInvoicesRegister() const
{
    QVector<oldInvoice> tmp;
    int i =0;

    while(i<invoicesRegister.size()){
        tmp.push_back(invoicesRegister[invoicesRegister.size()-1-i]);
        i++;
    }

    return tmp;
}

void database::setInvoicesRegister(const QVector<oldInvoice> &newInvoicesRegister)
{
    invoicesRegister = newInvoicesRegister;
}

database::database(QObject *parent)
    : QObject{parent}
{
    mProductsTypes = productsTypes;

    mPoductsTypesShorts = productsTypesShorts;

    paymentMethods = invoicePaymentMethods;
    isLoaded =  loadCustomers() &&
            loadSellers() &&
            //loadPaymentMethods() &&
            loadProducts() &&
            loadInvoicesRegister();
    //                dupaLoad();
}

bool database::loadCustomers(){

    QFile mfile(CustomersDatabasePath);
    QString tmp_text = " ";
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
    QString tmp_text = " ";
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
    QString tmp_text =  " ";
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

    std::sort(products.begin(),products.end(), [](product p1, product p2){
        return p1.getPolishName() < p2.getPolishName();
    });

    qDebug()<< "Succesfully loaded products database";
    return true;
}

bool database::loadInvoicesRegister()
{
    QFile mfile(InvoicesRegisterPath);
    QString tmp_text =  " ";
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
                qDebug()<<"Error during loading the invoices register";
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

    qDebug()<<"Succesfully loaded invoices register.";

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

//do not use if not necessery
bool database::loadCustomersFromOldRegister(){

    QFile mfile(("D:\\SzkolkaRoslinOpatow\\Application_deployment\\External_resources\\dupa.csv"));
    QString tmp_text = "";
    QStringList tmp_vec;
    oldInvoice oi;
    QDate tmp_date;
    int i=0;

    if (!mfile.open(QIODevice::ReadOnly))
    {
        qDebug() << "Unable to open old invoices register";
        return false;
    }
    QTextStream inStream(&mfile);

    do{
        tmp_text = inStream.readLine();

        tmp_vec = tmp_text.split(';');

        if(invoicesRegister.empty()) goto pierwszy;

        if( invoicesRegister.last().getInvoiceNumber() == tmp_vec[6]){
            InvoiceRecord irr(
                        tmp_vec[7],tmp_vec[10].toInt(),
                    tmp_vec[12].toDouble()
                    );
            invoicesRegister.last().addRecord(irr);

        }
        else{
pierwszy:
            qDebug()<<"aaa: "<<tmp_vec[0];
            tmp_date = QDate::fromString(tmp_vec[0], "dd.MM.yyyy");
            oi.setBillingDate(tmp_date);

            tmp_date = QDate::fromString(tmp_vec[1], "dd.MM.yyyy");
            oi.setLastModificationDate(tmp_date);

            oi.setSaleDate(oi.getBillingDate());

            oi.setSeller(sellers[0]);

            for(int i=1;i<=customers.size();i++){
                if(customers[i-1].getName() == tmp_vec[3]){
                    oi.setBuyer(customers[i-1]);
                    break;
                }
            }
            if(oi.getBuyer().getName() ==""){
                qDebug()<<"Błąd ustawienia nabywcy";
            }

            if(oi.getBuyer().getRecipers().size() != 0 && tmp_vec[4]!=""){
                for(const auto & r:oi.getBuyer().getRecipers()){
                    if(r.getName() == tmp_vec[4]){
                        oi.setRecip(r);
                        break;
                    }
                }
            }

            oi.setInvoiceNumber(tmp_vec[6].replace('.','/'));

            InvoiceRecord ir(
                        tmp_vec[7],tmp_vec[10].toInt(),
                    tmp_vec[12].toDouble()
                    );
            oi.addRecord(ir);

            if(tmp_vec[13] == "zapłacono gotówką"){
                oi.setPaymentDeadline(oi.getBillingDate());
                oi.setPaymentMethod("zapłacono gotówką");
            }
            else{
                oi.setPaymentDeadline(QDate::fromString(tmp_vec[13], "dd.MM.yyyy"));
                oi.setPaymentMethod(tmp_vec[5]);
            }

            oi.setIsPaid(tmp_vec[14] == "TAK");

            invoicesRegister.push_back(oi);
            oi.setRecords({});
        }
        ++i;
    }while(i<173);


    mfile.close();

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

        seller s(tmp_vec)   ;
        sellers.push_back(s);

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

const QStringList database::getProductsPolishNames(const QString & filter) const
{
    QStringList a;
    for(const auto & p: products){
        if(p.getPolishName().toLower().contains(filter.toLower()) ||
                p.getSpecies().toLower().contains(filter.toLower())){
            a.push_back(p.getPolishName()+" "+p.getSpecies());
        }
    }
    return a;
}

const QStringList database::getPaymentMethods() const{
    return paymentMethods;
}


