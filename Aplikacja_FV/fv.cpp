#include "fv.h"

FV::FV(QObject *parent)
    : QObject{parent}
{

}

bool FV::init()
{
    is_inited = this->FV_temp.load();
    return is_inited;
}

void FV::createLatexFV(){
    std::fstream temp;
    std::string tmp_text = "";
    temp.open(FVpath  + FVLDefaultFileName_Latex, std::ios::out);
    if (!temp)
    {
        qDebug() << "Unable to create FV file";
        exit(1);
    }

    temp << this->FV_temp.getPart(Prembula);

    temp << this->FV_temp.getPart(Ending);

    temp.close();
}

void FV::createPDFFV(){
    std::string tmp;
    tmp = "pdflatex -output-directory=" + FVpath +" " + FVpath + FVLDefaultFileName_Latex;
    system(tmp.c_str());

    for(const std::string a: filesToDelete){
        tmp = "del " +FVpath + a;
        system(tmp.c_str());
    }
}

void FV::createFV(){
    createLatexFV();
    createPDFFV();
}
