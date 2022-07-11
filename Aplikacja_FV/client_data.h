#ifndef CLIENT_DATA_H
#define CLIENT_DATA_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "config.h"

/*
To do:
dokończyć implementacje dodawania, usuwania i edytowania odbiorców i klientów
nie uzywać klasy nadrzednej tylko implementowac metody klienta w kliencie
*/

const std::string Reciper_rDatabaseFile = "Clients_database.csv";
const std::string EOFRecipersString = "!EndOfClients;;;;";
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

class Recipers_r
{
    std::vector<Reciper_r> Recipers;

public:
    bool load();
    bool saveInFile();
    void addReciper(Reciper_r);
    bool addClient(std::string, Client);
    bool removeReciper(std::string);
    bool removeClient(std::string);
    bool editReciper(Reciper_r);
    bool editClient(Client);
};

#endif // CLIENT_DATA_H
