#include "fvtemplate.h"

FVTemplate::FVTemplate(QObject *parent)
    : QObject{parent}
{

}

 keywords::keywords(){
     keyword_seller_bussines_full_name = "dupa1";
     keyword_seller_adress_1= "dupa12";
     keyword_seller_adress_2= "dupa13";
     keyword_seller_bussines_town= "dupa14";
     keyword_seller_name= "dupa15";
     keyword_producer_number= "dupa16";
     keyword_selling_date= "dupa17";
     keyword_seller_phone_numbers= "dupa18";
     keyword_buyer_bussines_full_name= "dupa8";
     keyword_buyer_adress_1= "dupa9";
     keyword_buyer_adress_2= "dupa19";
     keyword_buyer_nip= "dupa10";
     keyword_recipient_full_name= "dupa143";
     keyword_reciper_adress_1= "dupa123";
     keyword_reciper_adress_2= "dupa1122";
     keyword_invoice_number= "dupa12323";
     keyword_total_to_pay= "dupa1454";
     keyword_total_to_pay_in_words= "dupa1121";
     keyword_payment_method= "dupa12121";
     keyword_payment_date= "dupa14343";
     keyword_seller_account_number= "dupa11121";
}

std::string FVTemplate::getPart(FVTemplatePart a)
{
    return parts.at(a);
};

 std::vector<std::string>& FVTemplate::getAllParts(){
    return parts;
}


bool FVTemplate::load(const std::string path)
{
    std::fstream temp;
    std::string tmp_text = "";

    temp.open(resourcesPath + FVLTemplateDefaultFileName, std::ios::in);
    if (!temp)
    {
        std::cout << "Unable to open template file";
        exit(1);
    }

    unsigned int index = 0;

    do
    {
        tmp_text = "";
        parts.push_back(tmp_text);
        do
        {
            getline(temp, tmp_text);

            if (tmp_text != spacer && tmp_text != EOFString)
            {
                parts[index] += (tmp_text + "\n");
            }
        } while (tmp_text != spacer && tmp_text != EOFString);

        index++;
    } while (tmp_text != EOFString);

    temp.close();

    // std::cout<<"index: "<<index<<"Ending: "<<Ending<<std::endl;
    is_loaded = (Ending == (index-1));

    return is_loaded;
};


void FVTemplate::insertValuesIntoKeywords(){

//        std::vector<keywordsPars> keywordsDescript={
//        {"KEYWORD-SELLER-BUSSINES-FULL-NAME",keyword_seller_bussines_full_name},
//        {"KEYWORD-SELLER-ADRESS-1",keyword_seller_adress_1},
//        {"KEYWORD-SELLER-ADRESS-2",keyword_seller_adress_2},
//        {"KEYWORD-SELLER-BUSSINES-TOWN",keyword_seller_bussines_town},
//        {"KEYWORD-SELLER-NAME",keyword_seller_name},
//        {"KEYWORD-PRODUCER-NUMBER",keyword_producer_number},
//        {"KEYWORD-SELLING-DATE",keyword_selling_date},
//        {"KEYWORD-SELLER-PHONE-NUMBERS",keyword_seller_phone_numbers},
//        {"KEYWORD-BUYER-BUSSINES-FULL-NAME",keyword_buyer_bussines_full_name},
//        {"KEYWORD-BUYER-ADRESS-1",keyword_buyer_adress_1},
//        {"KEYWORD-BUYER-ADRESS-2",keyword_buyer_adress_2},
//        {"KEYWORD-BUYER-NIP",keyword_buyer_nip},
//        {"KEYWORD-RECIPIENT-FULL-NAME",keyword_recipient_full_name},
//        {"KEYWORD-RECIPER-ADRESS-1",keyword_reciper_adress_1},
//        {"KEYWORD-RECIPER-ADRESS-2 ",keyword_reciper_adress_2 },
//        {"KEYWORD-INVOICE-NUMBER",keyword_invoice_number},
//        {"KEYWORD-TOTAL-TO-PAY",keyword_total_to_pay},
//        {"KEYWORD-TOTAL-TO-PAY-IN-WORDS",keyword_total_to_pay_in_words},
//        {"KEYWORD-PAYMENT-METHOD",keyword_payment_method},
//        {"KEYWORD-PAYMENT-DATE",keyword_payment_date},
//        {"KEYWORD-SELLER-ACCOUNT-NUMBER",keyword_seller_account_number}
//    };

//    for(std::string & part : parts){
//        for(keywordsPars kp : keywordsDescript){
//            while(part.rfind(kp.keyword) != std::string::npos){
//                part.replace(part.rfind(kp.keyword), kp.keyword.length(),kp.value);
//            }
//        }
//    }
}

