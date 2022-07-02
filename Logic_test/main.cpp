#include <iostream>
#include "inc\\FVtemplate.hh"
#include "inc\\FV.hh"
#include "inc\\FVData.hh"

int main()
{
    FV f;

    if (!f.init())
    {
        std::cout << "Inicjalizacja fv nie powiodła sie";
        exit(1);
    }

    FVRecord a("tuja", 15, 16), b("jalowiec", 20, 5, 15);
    f.addRecord(a);
    f.addRecord(b);

    f.setAddingReciper(true);
    f.insertValuesIntoKeywords();
    f.createFV();

    // std::string keyword = "\%tuTwojeImie";
    // std::string a = "Pies poszedl sie jebac " +keyword+ " i nie wrocil";
    // std::cout<<a<<std::endl;

    
    // if(a.rfind(keyword) != std::string::npos){
    //     a.replace(a.rfind(keyword), keyword.length(),"Marcel");
    //     std::cout<<a<<std::endl;
    // }
    // else{
    //     std::cout<<"Nie odnaleziono string"<<std::endl;
    // }

    
}