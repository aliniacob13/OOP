/*
Aici am o mostenire in diamant. 
Am o clasa de baza Staff, care are 2 clase derivate Controlor si Casier.
Am o clasa Manager, care mosteneste Controlor si Casier. 
Astfel, Manager poate face operatiuni atat de Controlor cat si de Casier, avand in plus si alte atribute.
                  Staff
                 /    \
            Controlor  Casier
                 \    /
                  Manager
Iar clasa Manager este singleton, adica exista un singur obiect de tip Manager in program.
*/
#pragma once
#include <regex>
#include <iostream>
#include <string>
#include <mutex>
#include "Person.hpp"
#include "generate.hpp"
static const char RESET[] = "\033[0m";
static const char RED[] = "\033[31m";
static const char GREEN[] = "\033[32m";
std::regex email_pattern("^[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\\.[a-zA-Z0-9-.]+$");
class Staff
{
    const std::string nume;
    const std::string prenume;
    char *email;
    char *password;
    const std::string pozitie;
    const std::string id;

public:
    Staff(const std::string &nume, const std::string &prenume,
          const std::string &emailStr, const std::string &passwordStr, const std::string &pozitie, const std::string &id)
        : nume(nume), prenume(prenume),
          pozitie(pozitie), id(id)
    {
        email = new char[emailStr.size() + 1];
        std::strcpy(email, emailStr.c_str());
        password = new char[passwordStr.size() + 1];
        std::strcpy(password, passwordStr.c_str());
    }
    virtual ~Staff()
    {
        delete[] email;
        delete[] password;
    }
    virtual void displayInfo() = 0;
    std::string getNume() const { return nume; }
    std::string getPrenume() const { return prenume; }
    std::string getEmail() const { return email; }
    std::string getPassword() const { return password; }
    std::string getPozitie() const { return pozitie; }
    std::string getId() const { return id; }
    void set_password(const std::string &new_password)
    {
        delete[] password;
        password = new char[new_password.size() + 1];
        std::strcpy(password, new_password.c_str());
    }
    virtual std::string getPozitie() = 0;
    void set_email(const std::string &new_email)
    {
        delete[] email; 
        email = new char[new_email.size() + 1];
        std::strcpy(email, new_email.c_str());
    }
    friend std::istream &operator>>(std::istream &is, Staff *&p);
    friend std::ostream &operator<<(std::ostream &os, const Staff &p);
};

std::ostream &operator<<(std::ostream &os, const Staff &p)
{
    os << "Nume: " << p.nume << "\n"
       << "Prenume: " << p.prenume << "\n"
       << "Email: " << p.email << "\n"
       << "Parola: " << p.password << "\n"
       << "Pozitie: " << p.pozitie << "\n"
       << "ID: " << p.id << "\n";
    return os;
}
class Controlor : virtual public Staff
{
public:
    Controlor(const std::string &nume, const std::string &prenume,
              const std::string &emailStr, const std::string &passwordStr, const std::string &pozitie, const std::string &id)
        : Staff(nume, prenume, emailStr, passwordStr, pozitie, id) {}
    std::string getPozitie() override
    {
        return "Controlor";
    }
    void displayInfo() override
    {
        std::cout << "Controlor: " << getNume() << " " << getPrenume() << "\n"
                  << "Email: " << getEmail() << "\n"
                  << "Pozitie: " << getPozitie() << "\n";
    }
    void checkPasager(Person *p, const std::string &tipTransport);
};
void Controlor::checkPasager(Person *p, const std::string &tipTransport)
{
    if (auto pasager = dynamic_cast<CazNormal *>(p))
    {
        if (tipTransport == "Bus")
        {
            if (pasager->getBileteBusGratuite() > 0)
            {
                pasager->setBileteBusGratuite(pasager->getBileteBusGratuite() - 1);
                std::cout << GREEN << "Pasagerul are bilet valid de autobuz" << RESET << "\n";
            }
            else if (pasager->getBileteBus() > 0)
            {
                pasager->setBileteBus(pasager->getBileteBus() - 1);
                std::cout << GREEN << "Pasagerul are bilet valid de autobuz" << RESET << "\n";
            }
            else
            {
                std::cout << RED << "Pasagerul nu are bilet valid de autobuz" << RESET << "\n";
                std::cout << RED << "Amenda: 80 RON" << RESET << "\n";
                pasager->setFonduri(pasager->getFonduri() - 80);
            }
        }
        else if (tipTransport == "Metro")
        {
            if (pasager->getBileteMetroGratuite() > 0)
            {
                pasager->setBileteMetroGratuite(pasager->getBileteMetroGratuite() - 1);
                std::cout << GREEN << "Pasagerul are bilet valid de metrou" << RESET << "\n";
            }
            else if (pasager->getBileteMetro() > 0)
            {
                pasager->setBileteMetro(pasager->getBileteMetro() - 1);
                std::cout << GREEN << "Pasagerul are bilet valid de metrou" << RESET << "\n";
            }
            else
            {
                std::cout << RED << "Pasagerul nu are bilet valid de metrou" << RESET << "\n";
                std::cout << RED << "Amenda: 80 RON" << RESET << "\n";
                pasager->setFonduri(pasager->getFonduri() - 80);
            }
        }
    }
    else if (auto pasager = dynamic_cast<Student *>(p))
    {
        if (tipTransport == "Bus")
        {
            if (pasager->getBileteBusGratuite() > 0)
            {
                pasager->setBileteBusGratuite(pasager->getBileteBusGratuite() - 1);
                std::cout << GREEN << "Pasagerul are bilet valid de autobuz" << RESET << "\n";
            }
            else if (pasager->getBileteBus() > 0)
            {
                pasager->setBileteBus(pasager->getBileteBus() - 1);
                std::cout << GREEN << "Pasagerul are bilet valid de autobuz" << RESET << "\n";
            }
            else
            {
                std::cout << RED << "Pasagerul nu are bilet valid de autobuz" << RESET << "\n";
                std::cout << RED << "Amenda: 80 RON" << RESET << "\n";
                pasager->setFonduri(pasager->getFonduri() - 80);
            }
        }
        else if (tipTransport == "Metro")
        {
            if (pasager->getBileteMetroGratuite() > 0)
            {
                pasager->setBileteMetroGratuite(pasager->getBileteMetroGratuite() - 1);
                std::cout << GREEN << "Pasagerul are bilet valid de metrou" << RESET << "\n";
            }
            else if (pasager->getBileteMetro() > 0)
            {
                pasager->setBileteMetro(pasager->getBileteMetro() - 1);
                std::cout << GREEN << "Pasagerul are bilet valid de metrou" << RESET << "\n";
            }
            else
            {
                std::cout << RED << "Pasagerul nu are bilet valid de metrou" << RESET << "\n";
                std::cout << RED << "Amenda: 80 RON" << RESET << "\n";
                pasager->setFonduri(pasager->getFonduri() - 80);
            }
        }
    }
    else if (auto pasager = dynamic_cast<Pensionar *>(p))
    {
        std::cout << GREEN << "Pasagerul are bilet valid" << RESET << "\n";
    }
}

class Casier : virtual public Staff
{
public:
    Casier(const std::string &nume, const std::string &prenume,
           const std::string &emailStr, const std::string &passwordStr, const std::string &pozitie, const std::string &id)
        : Staff(nume, prenume, emailStr, passwordStr, pozitie, id) {}
    std::string getPozitie() override
    {
        return "Casier";
    }
    void displayInfo() override
    {
        std::cout << "Casier: " << getNume() << " " << getPrenume() << "\n"
                  << "Email: " << getEmail() << "\n"
                  << "Pozitie: " << getPozitie() << "\n";
    }
    void helpPasager(Person *p, const std::string &tipTransport, const std::string &biletAbonament);
};

void Casier::helpPasager(Person *p, const std::string &tipTransport, const std::string &biletAbonament)
{
    if (auto pasager = dynamic_cast<CazNormal *>(p))
    {
        if (biletAbonament == "Bilet")
        {
            if (tipTransport == "Bus")
            {
                if (pasager->getFonduri() < 3)
                {
                    std::cout << RED << "Fonduri insuficiente" << RESET << "\n";
                    return;
                }
                pasager->setFonduri(pasager->getFonduri() - 3);
                pasager->setBileteBus(pasager->getBileteBus() + 1);
                std::cout << GREEN << "Bilet de autobuz cumparat" << RESET << "\n";
            }
            else if (tipTransport == "Metro")
            {
                if (pasager->getFonduri() < 5)
                {
                    std::cout << RED << "Fonduri insuficiente" << RESET << "\n";
                    return;
                }
                pasager->setFonduri(pasager->getFonduri() - 5);
                pasager->setBileteMetro(pasager->getBileteMetro() + 1);
                std::cout << GREEN << "Bilet de metrou cumparat" << RESET << "\n";
            }
        }
        else if (biletAbonament == "Abonament")
        {
            std::cout << "Tip de abonament:\n";
            std::cout << "1. Zi\n";
            std::cout << "2. Saptamana\n";
            std::cout << "3. Luna\n";
            int tip;
            while (true)
            {
                std::cin >> tip;
                if (tip >= 1 && tip <= 3)
                    break;
                else
                    std::cout << RED << "Tip de abonament invalid" << RESET << "\n";
            }
            if (tipTransport == "Bus")
            {
                if (tip == 1)
                {
                    if (pasager->getFonduri() < 3)
                    {
                        std::cout << RED << "Fonduri insuficiente" << RESET << "\n";
                        return;
                    }
                    pasager->setFonduri(pasager->getFonduri() - 3);
                    pasager->setBileteBus(pasager->getBileteBus() + 2);
                    std::cout << GREEN << "Abonament de autobuz cumparat pentru o zi" << RESET << "\n";
                }
                else if (tip == 2)
                {
                    if (pasager->getFonduri() < 10)
                    {
                        std::cout << RED << "Fonduri insuficiente" << RESET << "\n";
                        return;
                    }
                    pasager->setFonduri(pasager->getFonduri() - 10);
                    pasager->setBileteBus(pasager->getBileteBus() + 14);
                    std::cout << GREEN << "Abonament de autobuz cumparat pentru o saptamana" << RESET << "\n";
                }
                else if (tip == 3)
                {
                    if (pasager->getFonduri() < 30)
                    {
                        std::cout << RED << "Fonduri insuficiente" << RESET << "\n";
                        return;
                    }
                    pasager->setFonduri(pasager->getFonduri() - 30);
                    pasager->setBileteBus(pasager->getBileteBus() + 60);
                    std::cout << GREEN << "Abonament de autobuz cumparat pentru o luna" << RESET << "\n";
                }
            }
            else if (tipTransport == "Metro")
            {
                if (tip == 1)
                {
                    if (pasager->getFonduri() < 5)
                    {
                        std::cout << RED << "Fonduri insuficiente" << RESET << "\n";
                        return;
                    }
                    pasager->setFonduri(pasager->getFonduri() - 5);
                    pasager->setBileteMetro(pasager->getBileteMetro() + 2);
                    std::cout << GREEN << "Abonament de metrou cumparat pentru o zi" << RESET << "\n";
                }
                else if (tip == 2)
                {
                    if (pasager->getFonduri() < 20)
                    {
                        std::cout << RED << "Fonduri insuficiente" << RESET << "\n";
                        return;
                    }
                    pasager->setFonduri(pasager->getFonduri() - 20);
                    pasager->setBileteMetro(pasager->getBileteMetro() + 14);
                    std::cout << GREEN << "Abonament de metrou cumparat pentru o saptamana" << RESET << "\n";
                }
                else if (tip == 3)
                {
                    if (pasager->getFonduri() < 50)
                    {
                        std::cout << RED << "Fonduri insuficiente" << RESET << "\n";
                        return;
                    }
                    pasager->setFonduri(pasager->getFonduri() - 50);
                    pasager->setBileteMetro(pasager->getBileteMetro() + 60);
                    std::cout << GREEN << "Abonament de metrou cumparat pentru o luna" << RESET << "\n";
                }
            }
        }
    }
    else if (auto pasager = dynamic_cast<Student *>(p))
    {
        if (biletAbonament == "Bilet")
        {
            if (tipTransport == "Bus")
            {
                if (pasager->getFonduri() < 3)
                {
                    std::cout << RED << "Fonduri insuficiente" << RESET << "\n";
                    return;
                }
                pasager->setFonduri(pasager->getFonduri() - 3);
                pasager->setBileteBus(pasager->getBileteBus() + 1);
                std::cout << GREEN << "Bilet de autobuz cumparat" << RESET << "\n";
            }
            else if (tipTransport == "Metro")
            {
                if (pasager->getFonduri() < 5)
                {
                    std::cout << RED << "Fonduri insuficiente" << RESET << "\n";
                    return;
                }
                pasager->setFonduri(pasager->getFonduri() - 5);
                pasager->setBileteMetro(pasager->getBileteMetro() + 1);
                std::cout << GREEN << "Bilet de metrou cumparat" << RESET << "\n";
            }
        }
        else if (biletAbonament == "Abonament")
        {
            std::cout << "Tip de abonament:\n";
            std::cout << "1. Zi\n";
            std::cout << "2. Saptamana\n";
            std::cout << "3. Luna\n";
            int tip;
            while (true)
            {
                std::cin >> tip;
                if (tip >= 1 && tip <= 3)
                    break;
                else
                    std::cout << RED << "Tip de abonament invalid" << RESET << "\n";
            }
            if (tipTransport == "Bus")
            {
                if (tip == 1)
                {
                    if (pasager->getFonduri() < 3)
                    {
                        std::cout << RED << "Fonduri insuficiente" << RESET << "\n";
                        return;
                    }
                    pasager->setFonduri(pasager->getFonduri() - 3);
                    pasager->setBileteBus(pasager->getBileteBus() + 2);
                    std::cout << GREEN << "Abonament de autobuz cumparat pentru o zi" << RESET << "\n";
                }
                else if (tip == 2)
                {
                    if (pasager->getFonduri() < 10)
                    {
                        std::cout << RED << "Fonduri insuficiente" << RESET << "\n";
                        return;
                    }
                    pasager->setFonduri(pasager->getFonduri() - 10);
                    pasager->setBileteBus(pasager->getBileteBus() + 14);
                    std::cout << GREEN << "Abonament de autobuz cumparat pentru o saptamana" << RESET << "\n";
                }
                else if (tip == 3)
                {
                    if (pasager->getFonduri() < 30)
                    {
                        std::cout << RED << "Fonduri insuficiente" << RESET << "\n";
                        return;
                    }
                    pasager->setFonduri(pasager->getFonduri() - 30);
                    pasager->setBileteBus(pasager->getBileteBus() + 60);
                    std::cout << GREEN << "Abonament de autobuz cumparat pentru o luna" << RESET << "\n";
                }
            }
            else if (tipTransport == "Metro")
            {
                if (tip == 1)
                {
                    if (pasager->getFonduri() < 5)
                    {
                        std::cout << RED << "Fonduri insuficiente" << RESET << "\n";
                        return;
                    }
                    pasager->setFonduri(pasager->getFonduri() - 5);
                    pasager->setBileteMetro(pasager->getBileteMetro() + 2);
                    std::cout << GREEN << "Abonament de metrou cumparat pentru o zi" << RESET << "\n";
                }
                else if (tip == 2)
                {
                    if (pasager->getFonduri() < 20)
                    {
                        std::cout << RED << "Fonduri insuficiente" << RESET << "\n";
                        return;
                    }
                    pasager->setFonduri(pasager->getFonduri() - 20);
                    pasager->setBileteMetro(pasager->getBileteMetro() + 14);
                    std::cout << GREEN << "Abonament de metrou cumparat pentru o saptamana" << RESET << "\n";
                }
                else if (tip == 3)
                {
                    if (pasager->getFonduri() < 50)
                    {
                        std::cout << RED << "Fonduri insuficiente" << RESET << "\n";
                        return;
                    }
                    pasager->setFonduri(pasager->getFonduri() - 50);
                    pasager->setBileteMetro(pasager->getBileteMetro() + 60);
                    std::cout << GREEN << "Abonament de metrou cumparat pentru o luna" << RESET << "\n";
                }
            }
        }
    }
    else if (auto pasager = dynamic_cast<Pensionar *>(p))
    {
        std::cout << GREEN << "Pasagerul are bilet valid(Pensionarii au transport nelimitat)" << RESET << "\n";
    }
}
class Manager : public Controlor, public Casier
{
public:
static Manager& getInstance(
    const std::string& nume,
    const std::string& prenume,
    const std::string& emailStr,
    const std::string& passwordStr,
    const std::string& pozitie,
    const std::string& id
) {
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mtx_);
        if (!instance_) {
            instance_ = new Manager(nume, prenume, emailStr, passwordStr, pozitie, id);
        }
    }
    return *instance_;
}

    std::string getPozitie() override
    {
        return "Manager";
    }
    void displayInfo() override
    {
        std::cout << "Manager: " << getNume() << " " << getPrenume() << "\n"
                  << "Email: " << getEmail() << "\n"
                  << "Pozitie: " << getPozitie() << "\n";
    }
    static Staff *createEmployee(std::string type);
    Manager(const Manager&)            = delete;
    Manager& operator=(const Manager&) = delete;
    
private:

Manager(const std::string& nume,
        const std::string& prenume,
        const std::string& emailStr,
        const std::string& passwordStr,
        const std::string& pozitie,
        const std::string& id)
  : Staff   (nume,prenume,emailStr,passwordStr,pozitie,id)
  , Controlor(nume,prenume,emailStr,passwordStr,pozitie,id)
  , Casier   (nume,prenume,emailStr,passwordStr,pozitie,id)
{}


inline static Manager* instance_ = nullptr;
inline static std::mutex  mtx_;

};
static Staff *createEmployee(std::string type)
{
    std::string nume, prenume, emailStr, password, pozitie, id;
    std::cout << "Introduceti numele:\n";
    std::cin >> nume;
    std::cout << "Introduceti prenumele:\n";
    std::cin >> prenume;
    std::cout << "Introduceti email-ul:\n";
    while (true)
    {
        std::cin >> emailStr;
        if (std::regex_match(emailStr, email_pattern))
            break;
        else
            std::cout << RED << "Email invalid. Introduceti un email valid:\n"
                      << RESET;
    }
    
    password = generateHelper::getHiddenPassword();
    std::cout << "Introduceti pozitia:\n";
    std::cout << "1. Controlor\n";
    std::cout << "2. Administrator\n";
    std::cout << "3. Manager\n";
    int poz;
    std::cin >> poz;
    while (poz < 1 || poz > 3)
    {
        std::cout << "Pozitie invalida. Alegeti din nou:\n";
        std::cin >> poz;
    }
    if (poz == 1)
        pozitie = "Controlor";
    else if (poz == 2)
        pozitie = "Administrator";
    else
        pozitie = "Manager";
    std::cout << "Introduceti ID-ul:\n";
    std::cin >> id;
    if (type == "Controlor")
    {
        return new Controlor(nume, prenume, emailStr, password, "Controlor", id);
    }
    else if (type == "Casier")
    {
        return new Casier(nume, prenume, emailStr, password, "Casier", id);
    }
    else
    {
        std::cerr << RED << "Invalid employee type: " << type << RESET << "\n";
        return nullptr;
    }
}
std::istream &operator>>(std::istream &is, Staff *&p)
{
    std::string nume, prenume, emailStr, passwordStr, pozitie, id;
    std::cout << "Introduceti numele:\n";
    is >> nume;
    std::cout << "Introduceti prenumele:\n";
    is >> prenume;
    std::cout << "Introduceti email-ul:\n";
    while (true)
    {
        is >> emailStr;
        if (std::regex_match(emailStr, email_pattern))
            break;
        else
            std::cout << RED << "Email invalid. Introduceti un email valid:\n"
                      << RESET;
    }
    passwordStr=generateHelper::getHiddenPassword();
    
    id=generateHelper::generateID(nume, prenume);
    std::cout << "ID-ul generat este: " << id << "\n";
    
    
    std::cout << "Introduceti pozitia:\n";
    std::cout << "1. Controlor\n";
    std::cout << "2. Casier\n";
    
    int poz;
    std::cin >> poz;
    while (poz < 1 || poz > 2)
    {
        std::cout << "Pozitie invalida. Alegeti din nou:\n";
        std::cin >> poz;
    }
    if (poz == 1)
        pozitie = "Controlor";
    else if (poz == 2)
        pozitie = "Casier";
    

    if (pozitie == "Controlor")
    {
        p = new Controlor(nume, prenume, emailStr, passwordStr, pozitie, id);
    }
    else if (pozitie == "Casier")
    {
        p = new Casier(nume, prenume, emailStr, passwordStr, pozitie, id);
    }
    else 
    {
        std::cout << RED << "Pozitie invalida" << RESET << "\n";
        return is;
    }
    return is;
}