#include "fv.h"

FV::FV(QObject *parent)
    : QObject{parent}
{

}

bool FV::init()
{
    is_inited = this->FV_temp.load();
    addReciper = true;
    return is_inited;
}

void FV::addRecord(const FVRecord & record){
    this->FV_data.addToRecords(record);
}

void FV::setAddingReciper(bool value){
    addReciper = value;
}

void FV::createLatexFV(){

    std::fstream temp;
    std::string tmp_text = "";
    int counter = 1;

    temp.open(FVpath  + FVLDefaultFileName_Latex, std::ios::out);
    if (!temp)
    {
        std::cout << "Unable to create FV file";
        exit(1);
    }

    std::vector<FVRecord> RecordsToTable = FV_data.getRecords();

    temp << this->FV_temp.getPart(Prembula);
    temp << this->FV_temp.getPart(Header);
    temp << this->FV_temp.getPart(SellerBuyerDataBeginning);

    if(addReciper){
         temp << this->FV_temp.getPart(Reciper);
    }

    temp << this->FV_temp.getPart(SellerBuyerDataEnding);
    temp << this->FV_temp.getPart(InvoiceNumberText);
    temp << this->FV_temp.getPart(MainTableBegining);

    for (const FVRecord &r : RecordsToTable)
    {
        temp << counter++ << FVTableElemSeparator_DefValue << r << std::endl;
    }

    temp << this->FV_temp.getPart(MainTableEnding);
    temp << this->FV_temp.getPart(MainTableSummmary);
    temp << this->FV_temp.getPart(PaymentData);
    temp << this->FV_temp.getPart(Ending);

    temp.close();
}

void FV::createPDFFV(){
    std::string tmp;
    tmp = "pdflatex -quiet -output-directory=" + FVpath +" " + FVpath + FVLDefaultFileName_Latex;
    system(tmp.c_str());

    for(const std::string a: filesToDelete){
        tmp = "del " +FVpath + a;
        system(tmp.c_str());
    }
}

void FV::insertValuesIntoKeywords(){

    FV_temp.insertValuesIntoKeywords();
}

void FV::createFV(){
    createLatexFV();
    createPDFFV();
}
