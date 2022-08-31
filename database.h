#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>

#include <customer.h>
#include <config.h>
#include <products.h>
#include <invoicebase.h>
#include <QMessageBox>

class database : public QObject
{
    Q_OBJECT
    bool isLoaded;
    QVector<customer> customers;
    QVector<seller> sellers;
    QVector<product> products;
    QVector<oldInvoice> invoicesRegister;
    QStringList paymentMethods;

    QStringList mProductsTypes;
    QStringList mPoductsTypesShorts;

public:
    explicit database(QObject *parent = nullptr);

    bool loadCustomers();
    bool loadSellers();
    bool loadPaymentMethods();
    bool loadProducts();
    bool loadInvoicesRegister();

    bool dupaLoad(){

        QFile mfile("D:\\SzkolkaRoslinOpatow\\Application_deployment\\External_resources\\dupa.csv");
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
    };

    bool getIsLoaded() const;

    const QString getLatestInvoiceNumber();

    const QVector<customer> &getCustomers() const;
    const QVector<seller> &getSellers() const;
    const QVector<product> &getProducts() const;

    void addInvoiceToRegister(const invoiceBase & ai);

public slots:
    bool saveInvoicesRegister()const;
    bool saveCustomers()const;
    bool saveSellers()const;
    bool saveProducts()const;

    //    void pushDatabase()const{
    //        qInfo()<<"Zapisuję dane, zaczekaj";
    //        system("git add -A");
    //        system("git commit -m\"Saving data after work\"");
    //        system("git push origin main");
    //    }

    void addCustomer(const QString & n,
                     const QString & a,
                     const QString & t,
                     const QString & pc,
                     const QString & NIP);
    void addReciper(const QString & cust,
                    const QString & n,
                    const QString & a,
                    const QString & t,
                    const QString & pc);
    void addProduct(const QString & type,
                    const QString & latinName,
                    const QString & polishName,
                    const QString & species,
                    const QString & registerNumber = "");

    const QStringList getCustomersNames()const;
    //returns recipers list for customer
    const QStringList getRecipersNames(const QString & custName);
    const QStringList getSellersNames()const;
    const QStringList getProductsPolishNames(const QString & filter = "") const;
    const QStringList getPaymentMethods()const;

    const QStringList getProductsTypes() const;
    const QStringList getProductsTypesShorts() const;

signals:
    void preInvAddRecord();
    void postInvAddRecord();
    void preInvRemoveRecord(int index);
    void postInvRemoveRecord();
};

#endif // DATABASE_H
