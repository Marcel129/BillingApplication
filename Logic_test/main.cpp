#include <iostream>
#include "inc\\FVtemplate.hh"
#include "inc\\FV.hh"
#include "inc\\FVData.hh"
#include "inc\\Client_data.hh"
#include "inc\\Plants_data.hh"
#include "inc\\config.hh"


int main()
{
    // FV f;

    // if (!f.init())
    // {
    //     std::cout << "Inicjalizacja fv nie powiodła sie";
    //     exit(1);
    // }

    // FVRecord a("tuja", 15, 16), b("jalowiec", 20, 5, 15);
    // f.addRecord(a);
    // f.addRecord(b);

    // f.setAddingReciper(true);
    // f.insertValuesIntoKeywords();
    // f.createFV();

//     std::fstream temp;
//     std::string tmp_text = "";

//     temp.open(resourcesPath + "1234.csv", std::ios::in);
//     if (!temp)
//     {
//         std::cout << "Unable to open template file";
//         exit(1);
//     }
// getline(temp, tmp_text);getline(temp, tmp_text);
//     std::cout<<"-"<<tmp_text<<"-"<<std::endl;

// Recipers_r c;
// c.load();
// if(!c.removeReciper("Powiat Opatowski")){
//     std::cout << "Nie odnaleziono odbiorcy"<<std::endl;
// }
// c.saveInFile();
Plants p;
p.load();

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