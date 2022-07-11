#ifndef FVTEMPLATE_H
#define FVTEMPLATE_H

#include <QObject>
#include <QDebug>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <windows.h>
#include "config.h"


const std::string spacer = "%-||-||-";
const std::string EOFString = "%-||-||--||-||--||-||-";
const std::string FVLDefaultFileName = "FakturaVAT";
const std::string FVLTemplateDefaultFileName = "Faktura_template.tex";
const std::string FVLDefaultFileName_Latex = FVLDefaultFileName + ".tex";

const std::vector<std::string> filesToDelete =
{
    FVLDefaultFileName + ".log",
    FVLDefaultFileName + ".tex",
    FVLDefaultFileName + ".aux"
};

//latex keywords
struct keywords{
    std::string keyword_seller_bussines_full_name ;
    std::string keyword_seller_adress_1;
    std::string keyword_seller_adress_2;
    std::string keyword_seller_bussines_town;
    std::string keyword_seller_name;
    std::string keyword_producer_number;
    std::string keyword_selling_date;
    std::string keyword_seller_phone_numbers;
    std::string keyword_buyer_bussines_full_name;
    std::string keyword_buyer_adress_1;
    std::string keyword_buyer_adress_2;
    std::string keyword_buyer_nip;
    std::string keyword_recipient_full_name;
    std::string keyword_reciper_adress_1;
    std::string keyword_reciper_adress_2;
    std::string keyword_invoice_number;
    std::string keyword_total_to_pay;
    std::string keyword_total_to_pay_in_words;
    std::string keyword_payment_method;
    std::string keyword_payment_date;
    std::string keyword_seller_account_number;

    keywords();
};

struct keywordsPars{
    std::string keyword;
    std::string value;
};

enum FVTemplatePart
{
    Prembula,
    Header,
    SellerBuyerDataBeginning,
    Reciper,
    SellerBuyerDataEnding,
    InvoiceNumberText,
    MainTableBegining,
    MainTableEnding,
    MainTableSummmary,
    PaymentData,
    Ending
};

class FVTemplate : public QObject
{
    Q_OBJECT
    std::vector<std::string> parts;
    bool is_loaded;

public:
    explicit FVTemplate(QObject *parent = nullptr);
    std::string getPart(FVTemplatePart a);
    std::vector<std::string>& getAllParts();
    bool load(const std::string path = FVpath);
    void insertValuesIntoKeywords();

public slots:


signals:

};

#endif // FVTEMPLATE_H
