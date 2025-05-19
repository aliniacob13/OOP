#pragma once
#include "Employees.hpp"
#include "Person.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>
class FileHelper
{
public:
    static std::vector<Staff *> readStaffFromFile(const std::string &filename); //citeste obiecte de tip Staff din fisier
    static std::vector<Person *> readPeopleFromFile(const std::string &); //citeste obiecte de tip Person din fisier
    static std::string trimTrailing(const std::string &str, const std::string &toRemove); 
    inline static std::string getID(const std::string &nume); //returneaza tipul unui obiect, in acest caz, elimina primul caracter
};
std::string FileHelper::getID(const std::string &nume)
{
    std::string id = nume.substr(1);
    return id;
}
std::string FileHelper::trimTrailing(const std::string &str, const std::string &toRemove)
{
    if (str.size() >= toRemove.size() &&
        str.compare(str.size() - toRemove.size(), toRemove.size(), toRemove) == 0)
    {
        return str.substr(0, str.size() - toRemove.size());
    }
    return str;
}
std::vector<Person *> FileHelper::readPeopleFromFile(const std::string &filename)
{
    std::vector<Person *> people;
    
    std::ifstream in(filename);
    if (!in.is_open())
    {
        std::cerr << "Error opening " << filename << "\n";
        return people;
    }

    std::string line;
    while (std::getline(in, line))
    {
        if (line.empty())
            continue;

        if (line.rfind("Caz:", 0) != 0)
        {
            std::cerr << "Expected 'Caz:' but got: " << line << "\n";
            break;
        }
        std::string type = line.substr(5);

        std::getline(in, line);
        auto nume = line.substr(line.find(":") + 2);

        std::getline(in, line);
        auto prenume = line.substr(line.find(":") + 2);

        std::getline(in, line);
        auto id = line.substr(line.find(":") + 2);

        std::getline(in, line);
        auto password = line.substr(line.find(":") + 2);

        std::getline(in, line);
        auto fondStr = line.substr(line.find(":") + 2);
        fondStr = trimTrailing(fondStr, " RON");
        float fonduri = std::stof(fondStr);

        Person *p = nullptr;
        if (type == "Pensionar")
        {
            std::getline(in, line);
            auto cnp = line.substr(line.find(":") + 2);
            std::getline(in, line);
            auto idTalon = line.substr(line.find(":") + 2);

            p = new Pensionar(nume, prenume, id, password, fonduri, cnp, idTalon);
        }
        else if (type == "CazNormal")
        {
            std::getline(in, line);
            int bBus = std::stoi(line.substr(line.find(":") + 2));
            std::getline(in, line);
            int bMetro = std::stoi(line.substr(line.find(":") + 2));
            std::getline(in, line);
            int bBusFree = std::stoi(line.substr(line.find(":") + 2));
            std::getline(in, line);
            int bMetroFree = std::stoi(line.substr(line.find(":") + 2));
            std::getline(in, line);
            int bBusConsumate = std::stoi(line.substr(line.find(":") + 2));
            std::getline(in, line);
            int bMetroConsumate = std::stoi(line.substr(line.find(":") + 2));

            auto cn = new CazNormal(nume, prenume, id, password, fonduri);
            cn->setBileteBus(bBus);
            cn->setBileteMetro(bMetro);
            cn->setBileteBusGratuite(bBusFree);
            cn->setBileteMetroGratuite(bMetroFree);
            cn->setBileteConsumateBus(bBusConsumate);
            cn->setBileteConsumateMetro(bMetroConsumate);
            p = cn;
        }
        else if (type == "Student")
        {
            std::getline(in, line);
            int bBus = std::stoi(line.substr(line.find(":") + 2));
            std::getline(in, line);
            int bMetro = std::stoi(line.substr(line.find(":") + 2));
            std::getline(in, line);
            int bBusFree = std::stoi(line.substr(line.find(":") + 2));
            std::getline(in, line);
            int bMetroFree = std::stoi(line.substr(line.find(":") + 2));
            std::getline(in, line);
            int bBusCons = std::stoi(line.substr(line.find(":") + 2));
            std::getline(in, line);
            int bMetroCons = std::stoi(line.substr(line.find(":") + 2));
            std::getline(in, line);
            auto cnp = line.substr(line.find(":") + 2);
            std::getline(in, line);
            auto studID = line.substr(line.find(":") + 2);

            auto st = new Student(nume, prenume, id, password, fonduri, cnp, studID);
            st->setBileteBus(bBus);
            st->setBileteMetro(bMetro);
            st->setBileteBusGratuite(bBusFree);
            st->setBileteMetroGratuite(bMetroFree);
            st->setBileteConsumateBus(bBusCons);
            st->setBileteConsumateMetro(bMetroCons);

            p = st;
        }
        else if (type == "CazSpecial")
        {
            std::getline(in, line);
            auto cnp = line.substr(line.find(":") + 2);
            std::getline(in, line);
            auto idTalon = line.substr(line.find(":") + 2);

            p = new Pensionar(nume, prenume, id, password, fonduri, cnp, idTalon);
        }
        else
        {
            std::cerr << "Unknown Caz type: " << type << "\n";
            break;
        }

        people.push_back(p);
    }

    return people;
}
std::vector<Staff *> FileHelper::readStaffFromFile(const std::string &filename)
{
    std::vector<Staff *> staffList;
    staffList.erase(staffList.begin(), staffList.end());
    std::ifstream in(filename);
    if (!in)
    {
        std::cerr << "Error opening " << filename << "\n";
        return staffList;
    }
    
    std::string line;
    while (true)
    {
        if (!std::getline(in, line))
            break;
        if (line.empty())
            continue;
        std::string nume = line.substr(6); 

        if (!std::getline(in, line))
            break;
        std::string prenume = line.substr(9); 

       
        if (!std::getline(in, line))
            break;
        std::string email = line.substr(7); 

        
        if (!std::getline(in, line))
            break;
        std::string parola = line.substr(8); 

        
        if (!std::getline(in, line))
            break;
        std::string pozitie = line.substr(9); 

        
        if (!std::getline(in, line))
            break;
        std::string id = line.substr(4); 

        Staff *p = nullptr;
        if (pozitie == "Controlor")
        {
            p = new Controlor(nume, prenume, email, parola, pozitie, id);
        }
        else if (pozitie == "Casier")
        {
            p = new Casier(nume, prenume, email, parola, pozitie, id);
        }
       

        staffList.push_back(p);
    }

    return staffList;
}