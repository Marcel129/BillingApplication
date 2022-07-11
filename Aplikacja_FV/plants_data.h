#ifndef PLANTS_DATA_H
#define PLANTS_DATA_H


#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include "config.h"

const std::string plantsDatabaseFile = "Plants_database.csv";
const unsigned int PlantsElementsCount = 5;

class Plant
{
    std::string type;
    std::string latinName;
    std::string polishName;
    std::string species;
    std::string regNo;

public:
    Plant(std::string t, std::string l, std::string p, std::string s, std::string r);
    Plant(std::vector<std::string> v);
    void setType(std::string n) { type = n; };
    std::string getType() const { return type; };
    void setLatinName(std::string n) { latinName = n; };
    std::string getLatinName() const { return latinName; };
    void setPolishName(std::string n) { polishName = n; };
    std::string getPolishName() const { return polishName; };
    void setSpecies(std::string n) { species = n; };
    std::string getSpecies() const { return species; };
    void setRegNo(std::string n) { regNo = n; };
    std::string getRegNo() const { return regNo; };
};

class Plants
{
    std::vector<Plant> plants;

public:
    bool load();
    bool saveInFile();
    void addPlant(Plant);
    bool removePlant(std::string);
    bool editPlant(std::string);
};

#endif // PLANTS_DATA_H
