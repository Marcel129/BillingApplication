#ifndef Reciper_r_DATA_HH
#define Reciper_r_DATA_HH

#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include "config.hh"

const std::string Reciper_rDatabaseFile = "Clients_database.csv";
const std::string EOFDataString = "!EndOfData";
const std::string EOFRecipersString = "!EndOfClients";
const std::string CSVSplitChar = ";";
const char CommentChar = '#';
const unsigned int ClientsElementsCount = 5;
const unsigned int Reciper_rElementsCount = 5;

class Client
{
    std::string name;
    std::string adress;
    std::string town;
    std::string postal_code;

public:
    Client(std::string n, std::string a, std::string t, std::string p);
    Client(std::vector<std::string> v);

    void setName(std::string n) { name = n; };
    std::string getName() const { return name; };
    void setAdress(std::string n) { adress = n; };
    std::string getAdress() const { return adress; };
    void setTown(std::string n) { town = n; };
    std::string getTown() const { return town; };
    void setPostal_Code(std::string n) { postal_code = n; };
    std::string getPostal_Code() const { return postal_code; };

};

class Reciper_r 
{
    std::vector<Client> Clients;
    std::string name;
    std::string adress;
    std::string town;
    std::string postal_code;
    std::string NIP;

public:
    Reciper_r(Client r, std::string n, std::string a, std::string t, std::string p, std::string ni);
    Reciper_r(std::vector<std::string> v);
    void addClient(Client r);
    bool removeClient(Client r);

    void setName(std::string n) { name = n; };
    std::string getName() const { return name; };
    void setAdress(std::string n) { adress = n; };
    std::string getAdress() const { return adress; };
    void setTown(std::string n) { town = n; };
    std::string getTown() const { return town; };
    void setPostal_Code(std::string n) { postal_code = n; };
    std::string getPostal_Code() const { return postal_code; };
    void setNIP(std::string n) { NIP = n; };
    std::string getNIP() const { return NIP; };
    std::vector<Client> getClients() const { return Clients; };
};

class Recipers_r{
    std::vector<Reciper_r> Recipers;

    public:
    bool load();
    bool saveInFile();
};

std::ostream &operator<<(std::ostream &os, const Client &c)
{
    // os << "Name: " << c.getName() << "\t"
    //    << "Adress: " << c.getAdress() << "\t"
    //    << "Town: " << c.getTown() << "\t"
    //    << "Postal code: " << c.getPostal_Code() << std::endl;
    os << c.getName() << CSVSplitChar
       << c.getAdress() << CSVSplitChar
       << c.getTown() << CSVSplitChar
       << c.getPostal_Code() << std::endl;
    return os;
}

std::ostream &operator<<(std::ostream &os, const Reciper_r &c)
{
    // std::vector<Client> r = c.getClients();

    // os << "Name: " << c.getName() << std::endl
    //    << "Adress: " << c.getAdress() << std::endl
    //    << "Town: " << c.getTown() << std::endl
    //    << "Postal code: " << c.getPostal_Code() << std::endl
    //    << "NIP: " << c.getNIP() << std::endl;

    // if (r.size() >= 0)
    // {
    //     os << "Clients for " << c.getName() << ":" << std::endl;
    //     for (Client re : r)
    //     {
    //         os << re;
    //     }
    // }
        os << "Name: " << c.getName() << std::endl
       << "Adress: " << c.getAdress() << std::endl
       << "Town: " << c.getTown() << std::endl
       << "Postal code: " << c.getPostal_Code() << std::endl
       << "NIP: " << c.getNIP() << std::endl;

    return os;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Client::Client(std::string n, std::string a, std::string t, std::string p)
{
    name = n;
    adress = a;
    town = t;
    postal_code = p;
}

Client::Client(std::vector<std::string> v)
{
    if (v.size() == ClientsElementsCount)
    {
        name = v[0];
        adress = v[1];
        town = v[2];
        postal_code = v[3];
        
    }
    else
    {
        name = "";
        adress = "";
        town = "";
        postal_code = "";
        
    }
}

void Reciper_r::addClient(Client r){
    Clients.push_back(r);
}

Reciper_r::Reciper_r(Client r, std::string n, std::string a, std::string t, std::string p, std::string ni)
{
    Clients.push_back(r);
    name = n;
    adress = a;
    town = t;
    postal_code = p;
    NIP = ni;
}

Reciper_r::Reciper_r(std::vector<std::string> v)
{
    if (v.size() == Reciper_rElementsCount)
    {
        name = v[0];
        adress = v[1];
        town = v[2];
        postal_code = v[3];
        NIP = v[4];
    }
    else
    {
        name = "";
        adress = "";
        town = "";
        postal_code = "";
        NIP = "";
    }
}

bool Recipers_r::load(){
    std::fstream temp;
    std::string tmp_text = "";
    std::vector<std::string>tmp_vec;

    temp.open(resourcesPath + Reciper_rDatabaseFile, std::ios::in);
    if (!temp)
    {
        std::cerr << "Unable to open template file";
        return false;
    }

//load recipers
    do
    {
        getline(temp, tmp_text);

        // ignore comments
        if (tmp_text[0] == CommentChar)
            continue;

        if (tmp_text.find(EOFRecipersString) == std::string::npos)
        {
            tmp_vec = splitString(tmp_text, CSVSplitChar);
            if (tmp_vec.size() == Reciper_rElementsCount)
            {
                Reciper_r c(tmp_vec);
                Recipers.push_back(c);
            }
        }

    } while (tmp_text.find(EOFRecipersString) == std::string::npos);

    tmp_text = "";
    // load clients
    do
    {
        getline(temp, tmp_text);

        // ignore comments
        if (tmp_text[0] == CommentChar)
            continue;

        if (tmp_text.find(EOFDataString) == std::string::npos)
        {
            tmp_vec = splitString(tmp_text, CSVSplitChar);
            if (tmp_vec.size() == ClientsElementsCount)
            {
                Client c(tmp_vec[1],tmp_vec[2],tmp_vec[3],tmp_vec[4]);

                for (Reciper_r &rec : Recipers)
                {
                    if (tmp_vec[0] == rec.getName())
                    {
                        rec.addClient(c);
                        break;
                    }
                }
            }
        }

    } while (tmp_text.find(EOFDataString) == std::string::npos);

    for(auto e: Recipers){
        std::cout << std::endl;
        std::cout << e << std::endl;
    }

    temp.close();

    return true;
}

bool Recipers_r::saveInFile()
{
    std::fstream temp;

    temp.open(resourcesPath + Reciper_rDatabaseFile, std::ios::out);
    if (!temp)
    {
        std::cerr << "Unable to open template file";
        return false;
    }


}

#endif