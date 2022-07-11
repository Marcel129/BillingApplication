#include "plants_data.h"

Plant::Plant(std::string t, std::string l, std::string p, std::string s, std::string r)
{
    type = t;
    latinName = l;
    polishName = p;
    species = s;
    regNo = r;
}

Plant::Plant(std::vector<std::string> v)
{
    if (v.size() == PlantsElementsCount)
    {
        type = v[0];
        latinName = v[1];
        polishName = v[2];
        species = v[3];
        regNo = v[4];
    }
}

std::ostream &operator<<(std::ostream &os, const Plant &c)
{
    os << c.getType() << CSVSplitChar
       << c.getLatinName() << CSVSplitChar
       << c.getPolishName() << CSVSplitChar
       << c.getSpecies() << CSVSplitChar
       << c.getRegNo() << std::endl;
    return os;
}

bool Plants::load()
{
    std::fstream temp;
    std::string tmp_text = "";
    std::vector<std::string> tmp_vec;

    temp.open(resourcesPath + plantsDatabaseFile, std::ios::in);
    if (!temp)
    {
        std::cerr << "Unable to open template file";
        return false;
    }

    // load plants
    do
    {
        getline(temp, tmp_text);

        // ignore comments
        if (tmp_text[0] == CommentChar)
            continue;

        if (tmp_text.find(EOFDataString) == std::string::npos)
        {
            tmp_vec = splitString(tmp_text, CSVSplitChar);
            if (tmp_vec.size() == PlantsElementsCount)
            {
                Plant c(tmp_vec);
                plants.push_back(c);

            }
        }

    } while (tmp_text.find(EOFDataString) == std::string::npos);

    for(auto e: plants){
        std::cerr << e << std::endl;
    }

    temp.close();

    return true;
}

bool Plants::saveInFile(){
    std::fstream temp;

    temp.open(resourcesPath + plantsDatabaseFile, std::ios::out);
    if (!temp)
    {
        std::cerr << "Unable to open template file";
        return false;
    }

    temp << "#Plants;;;;" << std::endl
         << "#Rodzaj;nazwa polska;nazwa łacińska;gatunek;numer ewidencyjny" << std::endl;
    for (const Plant &p : plants)
    {
        temp << p;
    }
    temp << EOFDataString << std::endl;

    temp.close();

    return true;
}
