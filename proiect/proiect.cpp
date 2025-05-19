#include <iostream>
#include <regex>
#include <string>
#include <vector>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <termios.h> 
#include <unistd.h>  
#include <cctype>
#include "Person.hpp"
#include "Employees.hpp"
#include <memory>
#include <typeinfo>
#include <cxxabi.h>
#include "ReadFromFile.hpp"
#include "menuHelper.hpp"
#include "generate.hpp"
int main()
{
    std::vector<Person *> clienti;
    std::vector<Staff *> staff;
    clienti = FileHelper::readPeopleFromFile("People.txt");
    staff = FileHelper::readStaffFromFile("Employees.txt");
    
    bool inSession = true;
    Manager *boss = &Manager::getInstance("Andrei", "Paun", "apaun@yahoo.com", "1234", "Manager", "AP1");
    // std::string client_staff=MenuHelper::promptClientOrStaff();

    while (inSession)
    {
        std::string client_staff = MenuHelper::promptClientOrStaff();
        if (client_staff == "client")
        {
            bool logout_client = false;
            while(!logout_client)
            {
            std::cout << "Aveti cont? (Da/Nu)\n";
            std::string DaNu;
            DaNu = MenuHelper::DaorNu();
            std::cout << DaNu << "\n";
            if (DaNu == "nu")
            {
                std::cout << "Va incadrati in caz special? (Da/Nu)\n";
                std::string raspuns;
                raspuns = MenuHelper::DaorNu();
                if (raspuns == "da")
                {
                    std::cout << "In ce categorie va incadrati:\n";
                    std::cout << "1. Pensionar\n";
                    std::cout << "2. Student\n";
                    int optiune = MenuHelper::choose_number_between_1_n(2);
                    if (optiune == 1)
                    {
                        Pensionar *pensionar = nullptr;
                        std::cin >> pensionar;
                        // h << "Caz: " << FileHelper::getID(typeid(*pensionar).name()) << "\n";
                        // h << *pensionar;
                        clienti.push_back(pensionar);
                    }
                    else if (optiune == 2)
                    {
                        Student *student = nullptr;
                        std::cin >> student;
                        // h << "Caz: " << FileHelper::getID(typeid(*student).name()) << "\n";
                        // h << *student;
                        clienti.push_back(student);
                    }
                }
                else if (raspuns == "nu")
                {
                    CazNormal *cazNormal = nullptr;
                    std::cin >> cazNormal;
                    // h << "Caz: " << FileHelper::getID(typeid(*cazNormal).name()) << "\n";
                    // h << *cazNormal;
                    clienti.push_back(cazNormal);
                }
            }
            else if (DaNu == "da")
            {
                std::cout << "Introduceti ID-ul:\n";
                std::string id;
                std::cin >> id;
                // std::cout << "Introduceti parola:\n";
                std::string password;
                password = generateHelper::getHiddenPassword();
                bool found_cont_client = false;
                for (auto &client : clienti)
                {
                    if (client->getId() == id && client->getPassword() == password)
                    {
                        found_cont_client = true;
                        std::cout << "Logare reusita!\n";
                        client->displayInfo();
                        bool logout = false;
                        while (!logout)
                        {
                            std::cout << "Ce doriti sa faceti?\n";
                            std::cout << "1. Depunere bani\n";
                            std::cout << "2. Cumparare bilet\n";
                            std::cout << "3. Cumparare abonament\n";
                            int choice = MenuHelper::choose_number_between_1_n(3);
                            if (choice == 1)
                            {
                                std::cout << "Introduceti suma pe care doriti sa o depuneti in cont:\n";
                                int suma;
                                std::cin >> suma;
                                while (suma < 0)
                                {
                                    std::cout << "Suma nu poate fi negativa. Introduceti o suma valida:\n";
                                    std::cin >> suma;
                                }
                                client->adaugFonduri(suma);
                                std::cout << "Suma a fost depusa cu succes!\n";
                            }
                            else if (choice == 2)
                            {
                                std::string tipTransport;
                                std::cout << "Alegeti tipul de transport (Bus/Metro):\n";
                                std::cout << "1. Bus\n";
                                std::cout << "2. Metro\n";
                                int tip;
                                tip = MenuHelper::choose_number_between_1_n(2);
                                if (tip == 1)
                                    tipTransport = "Bus";
                                else
                                    tipTransport = "Metro";
                                client->buyTicket(tipTransport);
                            }
                            else if (choice == 3)
                            {
                                std::string tipTransport, tipPass;
                                std::cout << "Alegeti tipul de transport:\n";
                                std::cout << "1. Bus\n";
                                std::cout << "2. Metro\n";
                                int tip;
                                tip = MenuHelper::choose_number_between_1_n(2);
                                if (tip == 1)
                                    tipTransport = "Bus";
                                else
                                    tipTransport = "Metro";

                                std::cout << "Alegeti tipul de abonament (Zi/Saptamanal/Lunar):\n";
                                std::cout << "1. Zi\n";
                                std::cout << "2. Saptamanal\n";
                                std::cout << "3. Lunar\n";
                                int tipAbonament;
                                tipAbonament = MenuHelper::choose_number_between_1_n(3);
                                if (tipAbonament == 1)
                                    tipPass = "Zi";
                                else if (tipAbonament == 2)
                                    tipPass = "Saptamana";
                                else
                                    tipPass = "Luna";
                                client->buyPass(tipTransport, tipPass);
                            }
                            else
                            {
                                std::cout << "Actiune nerecunoscuta!\n";
                            }
                            std::cout << "Doriti sa continuati? (Da/Nu)\n";
                            std::string continuare;
                            continuare = MenuHelper::DaorNu();
                            if (continuare == "nu")
                            {
                                logout = true;
                            }
                            else if (continuare == "da")
                            {
                                logout = false;
                            }
                        }
                        break;
                    }
                }
                if (!found_cont_client)
                    std::cout << "Contul nu a fost gasit!\n";
            }
            std::cout << "Doriti sa iesiti din sesiunea de client? (Da/Nu)\n";
            std::string iesire;
            iesire = MenuHelper::DaorNu();
            if(iesire == "da")
                logout_client = true;
            else
                logout_client = false;
        }
        
        }
        else if (client_staff == "staff")
        {
            bool logout_staff = false;
            bool logat=false;
            while(!logout_staff){
            std::cout << "Introduceti ID-ul dumneavoastra de staff:\n";
            std::string id;
            std::cin >> id;
            // std::cout<<"Introduceti parola:\n";
            std::string password;
            password = generateHelper::getHiddenPassword();
            if (boss->getId() == id and boss->getPassword() == password)
            {
                logat=true;
                std::cout << "Logare reusita!\n";
                std::cout << "Bine ati venit, domnule Paun!\n";
                bool logout = false;
                while (!logout)
                {
                    std::cout << "Ce doriti sa faceti?\n";
                    std::cout << "1. Adaugare angajat\n";
                    std::cout << "2. Stergere angajat\n";
                    std::cout << "3. Afisare angajati\n";
                    std::cout << "4. Verifica cetatean\n";
                    std::cout << "5. Ajuta cetatean\n";
                    std::cout << "6. Logout\n";
                    int optiune = MenuHelper::choose_number_between_1_n(6);
                    if (optiune == 1)
                    {
                        Staff *angajat = nullptr;
                        std::cin >> angajat;
                        staff.push_back(angajat);
                    }
                    else if (optiune == 2)
                    {
                        std::string id_to_delete;
                        std::cout << "Introduceti ID-ul angajatului: ";
                        
                       std::cin >> id_to_delete;

                       auto it = staff.end();
                       for (auto iter = staff.begin(); iter != staff.end(); ++iter) {
                           if ((*iter)->getId() == id_to_delete) {
                               it = iter;
                               break;
                           }
                       }                       
                       if (it != staff.end()) {
                           delete *it;
                           staff.erase(it);
                           std::cout << "Angajatul a fost sters cu succes!\n";
                       } else {
                           std::cout << "Angajatul nu a fost gasit!\n";
                       }
                    }
                    else if (optiune == 3)
                    {
                        if(staff.empty())
                            std::cout << "Nu exista angajati!\n";
                        else
                            std::cout << "Angajati:\n";
                        for (auto &s : staff)
                            std::cout << *s;
                    }
                    else if(optiune==4)
                    {
                        std::cout << "Introduceti ID-ul cetateanului: ";
                                std::string id;
                                std::cin >> id;
                                bool found_cetatean = false;
                                for (auto &c : clienti)
                                {
                                    if (c->getId() == id)
                                    {
                                        found_cetatean = true;
                                        std::cout << "Cetatean gasit!\n";
                                        std::cout << "In ce mijloc de transport se afla?\n";
                                        std::cout << "1. Bus\n";
                                        std::cout << "2. Metro\n";
                                        int tip;
                                        tip = MenuHelper::choose_number_between_1_n(2);
                                        std::string tipTransport;
                                        if (tip == 1)
                                            tipTransport = "Bus";
                                        else
                                            tipTransport = "Metro";
                                        boss->checkPasager(c, tipTransport);
                                        break;
                                    }
                                }
                                if(found_cetatean==false)
                                    std::cout << "Cetateanul nu a fost gasit!\n";
                    }
                    else if (optiune == 5)
                    {
                        std::string id;
                        std::cout << "Introduceti ID-ul cetateanului: ";
                        std::cin >> id;
                        bool found_cetatean = false;
                        for (auto &c : clienti)
                        {
                            if (c->getId() == id)
                            {
                                found_cetatean = true;
                                std::cout << "Cetatean gasit!\n";
                                std::cout << "Ce doriti sa faceti?\n";
                                std::cout << "1. Adaugare fonduri\n";
                                std::cout << "2. Adaugare bilet(e)\n";
                                std::cout << "3. Adaugare abonament\n";
                                int optiune;
                                optiune = MenuHelper::choose_number_between_1_n(3);
                                if (optiune == 1)
                                {
                                    std::cout << "Introduceti suma pe care doriti sa o adaugati: ";
                                    int suma;
                                    std::cin >> suma;
                                    while (suma < 0)
                                    {
                                        std::cout << "Suma nu poate fi negativa. Introduceti o suma valida:\n";
                                        std::cin >> suma;
                                    }
                                    c->adaugFonduri(suma);
                                    std::cout << "Suma a fost adaugata cu succes!\n";
                                }
                                else if (optiune == 2)
                                {
                                    std::string tipTransport;
                                    std::cout << "Alegeti tipul de transport:\n";
                                    std::cout << "1. Bus\n";
                                    std::cout << "2. Metro\n";
                                    int tip;
                                    tip = MenuHelper::choose_number_between_1_n(2);
                                    if (tip == 1)
                                        tipTransport = "Bus";
                                    else
                                        tipTransport = "Metro";
                                    boss->helpPasager(c, tipTransport, "Bilet");
                                }
                                else if (optiune == 3)
                                {
                                    std::string tipTransport, tipPass;
                                    std::cout << "Alegeti tipul de transport:\n";
                                    std::cout << "1. Bus\n";
                                    std::cout << "2. Metro\n";
                                    int tip;
                                    tip = MenuHelper::choose_number_between_1_n(2);
                                    if (tip == 1)
                                        tipTransport = "Bus";
                                    else
                                        tipTransport = "Metro";

                                    boss->helpPasager(c, tipTransport, "Abonament");
                                }
                                break;
                            }
                        }
                    }
                    else if (optiune == 6)
                    {
                        logout = true;
                    }
                }
            }
            else if (boss->getId() != id)
            {
                for (auto &s : staff)
                {
                    if (s->getId() == id and s->getPassword() == password)
                    {
                        logat=true;
                        std::cout << "Logare reusita!\n";
                        std::cout << "Bine ai venit, " << s->getNume() << " " << s->getPrenume() << "!\n";
                        std::string tip = FileHelper::getID(typeid(*s).name());
                        bool logout = false;
                        while (!logout)
                        {
                            if (tip == "Controlor")
                            {
                                Controlor *controlor = dynamic_cast<Controlor *>(s);
                                std::cout << "Introduceti ID-ul cetateanului: ";
                                std::string id;
                                std::cin >> id;
                                bool found_cetatean = false;
                                for (auto &c : clienti)
                                {
                                    if (c->getId() == id)
                                    {
                                        found_cetatean = true;
                                        std::cout << "Cetatean gasit!\n";
                                        std::cout << "In ce mijloc de transport se afla?\n";
                                        std::cout << "1. Bus\n";
                                        std::cout << "2. Metro\n";
                                        int tip;
                                        tip = MenuHelper::choose_number_between_1_n(2);
                                        std::string tipTransport;
                                        if (tip == 1)
                                            tipTransport = "Bus";
                                        else
                                            tipTransport = "Metro";
                                        controlor->checkPasager(c, tipTransport);
                                        break;
                                    }
                                }
                            }
                            else if (tip == "Casier")
                            {
                                Casier *casier = dynamic_cast<Casier *>(s);
                                std::cout << "Introduceti ID-ul cetateanului: ";
                                std::string id;
                                std::cin >> id;
                                bool found_cetatean = false;
                                for (auto &c : clienti)
                                {
                                    if (c->getId() == id)
                                    {
                                        found_cetatean = true;
                                        std::cout << "Cetatean gasit!\n";
                                        std::cout << "Ce doriti sa faceti?\n";
                                        std::cout << "1. Adaugare fonduri\n";
                                        std::cout << "2. Adaugare bilet(e)\n";
                                        std::cout << "3. Adaugare abonament\n";
                                        int optiune;
                                        optiune = MenuHelper::choose_number_between_1_n(3);
                                        if (optiune == 1)
                                        {
                                            std::cout << "Introduceti suma pe care doriti sa o adaugati: ";
                                            int suma;
                                            std::cin >> suma;
                                            while (suma < 0)
                                            {
                                                std::cout << "Suma nu poate fi negativa. Introduceti o suma valida:\n";
                                                std::cin >> suma;
                                            }
                                            c->adaugFonduri(suma);
                                            std::cout << "Suma a fost adaugata cu succes!\n";
                                        }
                                        else if (optiune == 2)
                                        {
                                            std::string tipTransport;
                                            std::cout << "Alegeti tipul de transport:\n";
                                            std::cout << "1. Bus\n";
                                            std::cout << "2. Metro\n";
                                            int tip;
                                            tip = MenuHelper::choose_number_between_1_n(2);
                                            if (tip == 1)
                                                tipTransport = "Bus";
                                            else
                                                tipTransport = "Metro";
                                            casier->helpPasager(c, tipTransport, "Bilet");
                                        }
                                        else if (optiune == 3)
                                        {
                                            std::string tipTransport, tipPass;
                                            std::cout << "Alegeti tipul de transport:\n";
                                            std::cout << "1. Bus\n";
                                            std::cout << "2. Metro\n";
                                            int tip;
                                            tip = MenuHelper::choose_number_between_1_n(2);
                                            if (tip == 1)
                                                tipTransport = "Bus";
                                            else
                                                tipTransport = "Metro";
                                            casier->helpPasager(c, tipTransport, "Abonament");
                                        }
                                        break;
                                    }
                                }
                                if(!found_cetatean)
                                    std::cout << "Cetateanul nu a fost gasit!\n";
                            }
                            std::cout << "Doriti sa iesiti din sesiune? (Da/Nu)\n";
                            std::string iesire;
                            iesire = MenuHelper::DaorNu();
                            if (iesire == "da")
                                logout = true;
                            else
                                logout = false;
                        }
                    }
                }
            }
            if(logat==false)
            {
                std::cout << "Logare nereusita! ID sau parola gresita!\n";
            }
            std::cout << "Doriti sa iesiti din sesiunea de staff? (Da/Nu)\n";
            std::string iesire;
            iesire = MenuHelper::DaorNu();
            if(iesire == "da")
                logout_staff = true;
            else
                logout_staff = false;
        }
        

        }
        std::string iesire;
        std::cout << "Doriti sa iesiti din aplicatie? (Da/Nu)\n";
        iesire = MenuHelper::DaorNu();
        if (iesire == "da")
            inSession = false;
        else
            inSession = true;
        }
        std::ofstream g("Employees.txt", std::ios::out | std::ios::trunc);
        std::ofstream h("People.txt", std::ios::out | std::ios::trunc);
        for (auto &c : clienti)
        {
            std::cout << "Tipul: " << FileHelper::getID(typeid(*c).name()) << "\n";
            std::cout << *c;
            h << "Caz: " << FileHelper::getID(typeid(*c).name()) << "\n";
            h << *c;
            delete c;
        }
        for (auto &s : staff)
        {
            g << *s;
            delete s;
        }
        
        staff.clear();
        clienti.clear();
        return 0;
}

