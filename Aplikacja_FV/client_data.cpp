#include "client_data.h"

void Recipers_r::addReciper(Reciper_r r)
{
    Recipers.push_back(r);
}

bool Recipers_r::addClient(std::string r, Client c)
{
    for (Reciper_r &rec : Recipers)
    {
        if (rec.getName() == r)
        {
            rec.addClient(c);
            return true;
        }
    }
    return false;
}

bool Recipers_r::removeReciper(std::string r)
{
    unsigned int i = 0;
    for (const Reciper_r &rec : Recipers)
    {
        if (rec.getName() == r)
        {
            Recipers.erase(Recipers.begin() + i);
            return true;
        }
        ++i;
    }
    return false;
}

bool Recipers_r::removeClient(std::string c)
{
    return false;
}

bool Recipers_r::editReciper(Reciper_r r)
{
    return false;
}

bool Recipers_r::editClient(Client c)
{
    return false;
}

std::ostream &operator<<(std::ostream &os, const Client &c)
{
    os << c.getName() << CSVSplitChar
       << c.getAdress() << CSVSplitChar
       << c.getTown() << CSVSplitChar
       << c.getPostal_Code() << std::endl;
    return os;
}

std::ostream &operator<<(std::ostream &os, const Reciper_r &c)
{
    os << c.getName() << CSVSplitChar
       << c.getAdress() << CSVSplitChar
       << c.getTown() << CSVSplitChar
       << c.getPostal_Code() << CSVSplitChar
       << c.getNIP() << std::endl;

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

void Reciper_r::addClient(Client r)
{
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

bool Recipers_r::load()
{
    std::fstream temp;
    std::string tmp_text = "";
    std::vector<std::string> tmp_vec;

    temp.open(resourcesPath + Reciper_rDatabaseFile, std::ios::in);
    if (!temp)
    {
        std::cerr << "Unable to open template file";
        return false;
    }

    // load recipers
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
                Client c(tmp_vec[1], tmp_vec[2], tmp_vec[3], tmp_vec[4]);

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

    temp.close();

    return true;
}

bool Recipers_r::saveInFile()
{
    std::fstream temp;
    std::vector<Client> cl;

    temp.open(resourcesPath + Reciper_rDatabaseFile, std::ios::out);
    if (!temp)
    {
        std::cerr << "Unable to open template file";
        return false;
    }

    temp << "#Clients;;;;" << std::endl
         << "#Odbiorca;adres;miasto;kod_pocztowy;nip" << std::endl;
    for (const Reciper_r &r : Recipers)
    {
        temp << r;
    }
    temp << EOFRecipersString << std::endl
         << "#Recipers;;;;" << std::endl
         << "#Odbiorca;nabywca;adres;miasto;kod_pocztowy" << std::endl;
    for (const Reciper_r &r : Recipers)
    {
        if (!(cl = r.getClients()).empty())
        {
            for (const Client &c : cl)
            {
                temp << r.getName() << CSVSplitChar << c;
            }
        }
    }
    temp << EOFDataString << std::endl;

    temp.close();

    return true;
}
