/*
Am clasa abstracta Person
CazNormal mosteneste Person, iar clasa Student mosteneste CazNormal
Pensionar mosteneste Person
Am folosit protected ca sa pot accesa din clasele derivate, in caz de vreau sa afisez dintr-un vector de tip Person
Studentii au 20% reducere, iar pensionarii au gratuitate 100%.
*/
#pragma once
#include <iostream>
#include <string>
#include <limits>
#include "generate.hpp"
#include "menuHelper.hpp"
class Person{
    const std::string nume;
    const std::string prenume;
    const std::string id;
    const std::string password;
    float fonduri;
protected:
virtual void print(std::ostream& os) const {
  os
    << "Nume: "     << nume     << "\n"
    << "Prenume: "  << prenume  << "\n"
    << "ID: "       << id       << "\n"
    << "Password: " << password << "\n"
    << "Fonduri: "  << fonduri  << " RON\n";
}
public:
    Person(std::string nume, std::string prenume, std::string id, std::string password, float fonduri)
        : nume(nume), prenume(prenume), id(id), password(password), fonduri(fonduri) {}
    Person(const Person &other)
        : nume(other.nume), prenume(other.prenume), id(other.id), password(other.password) {}    
    virtual ~Person() {};
    virtual void displayInfo() = 0;
    virtual void buyTicket(const std::string &tipTransport) = 0;

    std::string getNume() const { return nume; }
    std::string getPrenume() const { return prenume; }
    std::string getId() const { return id; }
    std::string getPassword() const { return password; }
    float getFonduri() const { return fonduri; }
    void setFonduri(int f) { fonduri = f; }
    void adaugFonduri(int f) { fonduri += f; }
    friend std::istream &operator>>(std::istream &is, Person *&p);
    friend std::ostream &operator<<(std::ostream &os, const Person &p);
    virtual void buyPass(const std::string &tipTransport, const std::string &tipPass) = 0;
};
std::ostream &operator<<(std::ostream &os, const Person &p)
{
    p.print(os);
    return os;
}
class CazNormal : public Person{
    int bileteBus;
    int bileteMetro;
    int bileteBusGratuite;
    int bileteMetroGratuite;
    int bileteConsumateBus;
    int bileteConsumateMetro;
protected:
    void print(std::ostream& os) const override {
        Person::print(os);
        os
            << "Bilete Bus: " << bileteBus << "\n"
            << "Bilete Metro: " << bileteMetro << "\n"
            << "Bilete Bus Gratuite: " << bileteBusGratuite << "\n"
            << "Bilete Metro Gratuite: " << bileteMetroGratuite << "\n"
            << "Bilete Consumate Bus: " << bileteConsumateBus << "\n"
            << "Bilete Consumate Metro: " << bileteConsumateMetro << "\n";
    }
public:
    CazNormal(std::string nume, std::string prenume, std::string id, std::string password, float fonduri)
        : Person(nume, prenume, id, password, fonduri), bileteBus(0), bileteMetro(0), bileteBusGratuite(0), bileteMetroGratuite(0), bileteConsumateBus(0), bileteConsumateMetro(0) {}
    void displayInfo() override {
        std::cout << "Caz Normal: " << getNume() << " " << getPrenume() << "\n"
                  << "ID: " << getId() << "\n"
                  << "Fonduri: " << getFonduri() << "\n"
                  << "Bilete Bus: " << bileteBus << "\n"
                  << "Bilete Metro: " << bileteMetro << "\n"
                  << "Bilete Bus Gratuite: " << bileteBusGratuite << "\n"
                  << "Bilete Metro Gratuite: " << bileteMetroGratuite << "\n"
                    << "Bilete Consumate Bus: " << bileteConsumateBus << "\n"
                    << "Bilete Consumate Metro: " << bileteConsumateMetro << "\n";
    }
    int getBileteBus() const { return bileteBus; }
    int getBileteMetro() const { return bileteMetro; }
    int getBileteBusGratuite() const { return bileteBusGratuite; }
    int getBileteMetroGratuite() const { return bileteMetroGratuite; }
    int getBileteConsumateBus() const { return bileteConsumateBus; }
    int getBileteConsumateMetro() const { return bileteConsumateMetro; }
    CazNormal(const CazNormal &other)
        : Person(other), bileteBus(other.bileteBus), bileteMetro(other.bileteMetro),
          bileteBusGratuite(other.bileteBusGratuite), bileteMetroGratuite(other.bileteMetroGratuite) {}
    void setBileteBus(int b) { bileteBus = b; }
    void setBileteMetro(int m) { bileteMetro = m; }
    void setBileteBusGratuite(int b) { bileteBusGratuite = b; }
    void setBileteMetroGratuite(int m) { bileteMetroGratuite = m; }
    void setBileteConsumateBus(int b) { bileteConsumateBus = b; }
    void setBileteConsumateMetro(int m) { bileteConsumateMetro = m; }
    friend std::istream &operator>>(std::istream &is, CazNormal *&caz);
    friend std::ostream &operator<<(std::ostream &os, const CazNormal &caz);
    void buyTicket(const std::string &tipTransport) override;
    void buyPass(const std::string &tipTransport, const std::string &tipPass) override;
};
void CazNormal::buyPass(const std::string &tipTransport, const std::string &tipPass)
{
    if(tipTransport=="Metro")
    {
        if(tipPass=="Zi")
        {
            if(getFonduri()<5)
            {
                std::cout<<"Fonduri insuficiente\n";
                return;
            }
            setFonduri(getFonduri()-5);
            bileteMetro+=2;
            std::cout<<"Abonament Metro cumparat pentru o zi\n";
        }
        else if(tipPass=="Saptamana")
        {
            if(getFonduri()<20)
            {
                std::cout<<"Fonduri insuficiente\n";
                return;
            }
            setFonduri(getFonduri()-20);
            bileteMetro+=14;
            std::cout<<"Abonament Metro cumparat pentru o saptamana\n";
        }
        else if(tipPass=="Luna")
        {
            if(getFonduri()<50)
            {
                std::cout<<"Fonduri insuficiente\n";
                return;
            }
            setFonduri(getFonduri()-50);
            bileteMetro+=60;
            std::cout<<"Abonament Metro cumparat pentru o luna\n";
        }
        else
        {
            std::cout<<"Tip de abonament invalid\n";
        }
    }
    else if(tipTransport=="Bus")
    {
        if(tipPass=="Zi")
        {
            if(getFonduri()<3)
            {
                std::cout<<"Fonduri insuficiente\n";
                return;
            }
            setFonduri(getFonduri()-3);
            bileteBus+=2;
            std::cout<<"Abonament Bus cumparat pentru o zi\n";
        }
        else if(tipPass=="Saptamana")
        {
            if(getFonduri()<10)
            {
                std::cout<<"Fonduri insuficiente\n";
                return;
            }
            setFonduri(getFonduri()-10);
            bileteBus+=14;
            std::cout<<"Abonament Bus cumparat pentru o saptamana\n";
        }
        else if(tipPass=="Luna")
        {
            if(getFonduri()<30)
            {
                std::cout<<"Fonduri insuficiente\n";
                return;
            }
            setFonduri(getFonduri()-30);
            bileteBus+=60;
            std::cout<<"Abonament Bus cumparat pentru o luna\n";
        }
        else
        {
            std::cout<<"Tip de abonament invalid\n";
        }
    }
    else
    {
        std::cout<<"Tip de transport invalid\n";
    }
}
std::istream &operator>>(std::istream &is, CazNormal *&p){
    std::string nume, prenume, id, password;
    float fonduri;
    std::cout<<"Introduceti numele:\n";
    is>>nume;
    std::cout<<"Introduceti prenumele:\n";
    is>>prenume;
    password=generateHelper::getHiddenPassword();
    id=generateHelper::generateID(nume, prenume);
    std::cout<<"ID generat: "<<id<<"\n";
    
    
    std::cout<<"Introduceti fondurile:\n";
    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    fonduri=MenuHelper::read_non_negative_amount(is);
    p=new CazNormal(nume, prenume, id, password, fonduri);
    return is;
}
std::ostream &operator<<(std::ostream &os, const CazNormal &p) {
    os
      << "Nume: "    << p.getNume()      << "\n"
      << "Prenume: " << p.getPrenume()   << "\n"
      << "ID: "      << p.getId()        << "\n"
      << "Password: "<< p.getPassword()  << "\n"
      << "Fonduri: " << p.getFonduri()   << " RON\n"
      << "Bilete Bus: "    << p.bileteBus      << "\n"
      << "Bilete Metro: "  << p.bileteMetro    << "\n"
      << "Bilete Bus Gratuite: "   << p.bileteBusGratuite   << "\n"
      << "Bilete Metro Gratuite: " << p.bileteMetroGratuite << "\n"
        << "Bilete Consumate Bus: "  << p.bileteConsumateBus  << "\n"
        << "Bilete Consumate Metro: " << p.bileteConsumateMetro << "\n";
    return os;
}
void CazNormal::buyTicket(const std::string &tipTransport) {
    if (tipTransport == "Bus") {
        
        if (bileteBusGratuite > 0) {
            --bileteBusGratuite;
            std::cout << "Folosit bilet gratuit bus\n";
            return;
        }
        
        if (getFonduri() < 3) {
            std::cout << "Fonduri insuficiente\n";
            return;
        }
        setFonduri(getFonduri() - 3);
        
        ++bileteBus;
        std::cout << "Bilet bus cumparat\n";

        
        if (bileteConsumateBus % 5 == 0 and bileteConsumateBus != 0) {
            ++bileteBusGratuite;
            std::cout << "Felicitari, ai primit un bilet gratuit de bus!\n";
        }
    }
    else if (tipTransport == "Metro") {
        if (bileteMetroGratuite> 0) {
            --bileteMetroGratuite;
            std::cout << "Folosit bilet gratuit metro\n";
            return;
        }
        if (getFonduri() < 5) {
            std::cout << "Fonduri insuficiente\n";
            return;
        }
        setFonduri(getFonduri() - 5);
        ++bileteMetro;
        
        std::cout << "Bilet metro cumparat\n";

        if (bileteConsumateMetro % 5 == 0 and bileteConsumateMetro != 0) {
            ++bileteMetroGratuite;
            std::cout << "Felicitari, ai primit un bilet gratuit de metro!\n";
        }
    }
    else {
        std::cout << "Tip transport invalid (\"Bus\" sau \"Metro\" doar)\n";
    }
}

class Pensionar : public Person{
    const std::string cnp;
    const std::string IDtalon;
protected:
void print(std::ostream& os) const override {
  Person::print(os);
  os<< "CNP: "<< cnp<< "\n"<< "ID Talon: "<< IDtalon << "\n";
}
public:
    Pensionar(std::string nume, std::string prenume, std::string id, std::string password, float fonduri, std::string cnp, std::string IDtalon)
        : Person(nume, prenume, id, password, fonduri), cnp(cnp), IDtalon(IDtalon) {}
    void displayInfo() override {
        std::cout << "Pensionar: " << getNume() << " " << getPrenume() << "\n"
                  << "ID: " << getId() << "\n"
                  << "Fonduri: " << getFonduri() << "\n"
                  << "CNP: " << cnp << "\n"
                  << "ID Talon: " << IDtalon << "\n";
    }
    
    std::string getCNP() const { return cnp; }
    std::string getIDtalon() const { return IDtalon; }
    
    Pensionar(const Pensionar &other)
        : Person(other), cnp(other.cnp), IDtalon(other.IDtalon) {}
    friend std::istream &operator>>(std::istream &is, Pensionar *&p);
    friend std::ostream &operator<<(std::ostream &os, const Pensionar &p);
    void buyTicket(const std::string &tipTransport) override {
        std::cout << "Pensionarii nu trebuie sa cumpere bilete, au gratuitate.\n";
    }
    void buyPass(const std::string &tipTransport, const std::string &tipPass) override {
        std::cout << "Pensionarii nu trebuie sa cumpere abonamente, au gratuitate.\n";
    }
};
std::istream &operator>>(std::istream &is, Pensionar *&p){
    std::string nume, prenume, id, password, cnp, IDtalon;
    float fonduri;
    std::cout<<"Introduceti numele:\n";
    is>>nume;
    std::cout<<"Introduceti prenumele:\n";
    is>>prenume;
    id=generateHelper::generateID(nume, prenume);
    password=generateHelper::getHiddenPassword();
    std::cout<<"ID generat: "<<id<<"\n";
    
    fonduri=1e5;
    std::cout<<"Introduceti CNP-ul:\n";
    is>>cnp;
    std::cout<<"Introduceti ID-ul talonului:\n";
    is>>IDtalon;
    p=new Pensionar(nume, prenume, id, password, fonduri, cnp, IDtalon);
    return is;
}
std::ostream &operator<<(std::ostream &os, const Pensionar &p) {
    os
      << "Nume: "    << p.getNume()      << "\n"
      << "Prenume: " << p.getPrenume()   << "\n"
      << "ID: "      << p.getId()        << "\n"
      << "Password: "<< p.getPassword()  << "\n"
      << "Fonduri: " << p.getFonduri()   << " RON\n"
      << "CNP: "     << p.getCNP()       << "\n"
      << "ID Talon: "<< p.getIDtalon()   << "\n";
    return os;
}

class Student : public CazNormal{
    const std::string cnp;
    const std::string studentID;
protected:
void print(std::ostream& os) const override {
  CazNormal::print(os);
  os<< "CNP: "<< cnp<< "\n"<< "Student ID: "<< studentID << "\n";
}
public:
        

    Student(std::string nume, std::string prenume, std::string id, std::string password, float fonduri, std::string cnp, std::string studentID)
        : CazNormal(nume, prenume, id, password, fonduri), cnp(cnp), studentID(studentID) {}
    void displayInfo() override {
        std::cout << "Student: " << getNume() << " " << getPrenume() << "\n"
                  << "ID: " << getId() << "\n"
                  << "Fonduri: " << getFonduri() << "\n"
                    << "Bilete Bus: " << getBileteBus() << "\n"
                    << "Bilete Metro: " << getBileteMetro() << "\n"
                    << "Bilete Bus Gratuite: " << getBileteBusGratuite() << "\n"
                    << "Bilete Metro Gratuite: " << getBileteMetroGratuite() << "\n"
                    << "Bilete Consumate Bus: " << getBileteConsumateBus() << "\n"
                    << "Bilete Consumate Metro: " << getBileteConsumateMetro() << "\n"
                  << "CNP: " << cnp << "\n"
                  << "Student ID: " << studentID << "\n";
    }
    
    std::string getCNP() const { return cnp; }
    std::string getStudentID() const { return studentID; }
    Student(const Student &other)
        : CazNormal(other), cnp(other.cnp), studentID(other.studentID) {}
    friend std::istream &operator>>(std::istream &is, Student *&p);
    friend std::ostream &operator<<(std::ostream &os, const Student &p);
    void buyTicket(const std::string &tipTransport) override;
    void buyPass(const std::string &tipTransport, const std::string &tipPass) override;
};
std::istream &operator>>(std::istream &is, Student *&p){
    std::string nume, prenume, id, password, cnp, studentID;
    float fonduri;
    std::cout<<"Introduceti numele:\n";
    is>>nume;
    std::cout<<"Introduceti prenumele:\n";
    is>>prenume;
    id=generateHelper::generateID(nume, prenume);
    password=generateHelper::getHiddenPassword();
    std::cout<<"ID generat: "<<id<<"\n";
    std::cout<<"Introduceti fondurile:\n";
    fonduri=-1;
    while(fonduri<0){
        is>>fonduri;
        
        try {
            if (fonduri < 0) {
                throw std::invalid_argument("Fondurile nu pot fi negative.");
            }
        } catch (const std::invalid_argument &e) {
            std::cout << e.what() << " Introduceti o suma valida:\n";
        }
    }
    std::cout<<"Introduceti CNP-ul:\n";
    is>>cnp;
    std::cout<<"Introduceti ID-ul studentului:\n";
    is>>studentID;
    p=new Student(nume, prenume, id, password, fonduri, cnp, studentID);
    return is;
}
std::ostream &operator<<(std::ostream &os, const Student &p) {
    os
      << "Nume: "    << p.getNume()      << "\n"
      << "Prenume: " << p.getPrenume()   << "\n"
      << "ID: "      << p.getId()       << "\n"
      << "Password: "<< p.getPassword()  << "\n"
      << "Fonduri: " << p.getFonduri()   << " RON\n"
        << "Bilete Bus: " << p.getBileteBus() << "\n"
        << "Bilete Metro: " << p.getBileteMetro() << "\n"
        << "Bilete Bus Gratuite: " << p.getBileteBusGratuite() << "\n"
        << "Bilete Metro Gratuite: " << p.getBileteMetroGratuite() << "\n"
        << "Bilete Consumate Bus: " << p.getBileteConsumateBus() << "\n"
        << "Bilete Consumate Metro: " << p.getBileteConsumateMetro() << "\n"
      << "CNP: "     << p.cnp      << "\n"
      << "Student ID: "<< p.studentID  << "\n";
    return os;
}
void Student::buyTicket(const std::string &tipTransport) {
    if (tipTransport == "Bus") {
        if (getBileteBusGratuite() > 0) {
            setBileteBusGratuite(getBileteBusGratuite() - 1);
            std::cout << "Folosit bilet gratuit bus\n";
            return;
        }
        if (getFonduri() < 3*0.8) {
            std::cout << "Fonduri insuficiente\n";
            return;
        }
        setFonduri(getFonduri() - 3*0.8);
        
        setBileteBus(getBileteBus() + 1);
        //setBileteConsumateBus(getBileteConsumateBus() + 1);
        std::cout << "Bilet bus cumparat\n";

        
        if (getBileteConsumateBus() % 5 == 0 and getBileteConsumateBus() != 0) {
            setBileteBusGratuite(getBileteBusGratuite() + 1);
            std::cout << "Felicitari, ai primit un bilet gratuit de bus!\n";
        }
    }
    else if (tipTransport == "Metro") {
        if (getBileteMetroGratuite() > 0) {
            setBileteMetroGratuite(getBileteMetroGratuite() - 1);
            std::cout << "Folosit bilet gratuit metro\n";
            return;
        }
        if (getFonduri() < 5*0.8) {
            std::cout << "Fonduri insuficiente\n";
            return;
        }
        setFonduri(getFonduri() - 5*0.8);
        setBileteMetro(getBileteMetro() + 1);
        //setBileteConsumateMetro(getBileteConsumateMetro() + 1);
        std::cout << "Bilet metro cumparat\n";
        if (getBileteConsumateMetro() % 5 == 0 and getBileteConsumateMetro() != 0) {
            setBileteMetroGratuite(getBileteMetroGratuite() + 1);
            std::cout << "Felicitari, ai primit un bilet gratuit de metro!\n";
        }
    }
    else {
        std::cout << "Tip transport invalid (\"Bus\" sau \"Metro\" doar)\n";
    }
}
void Student::buyPass(const std::string &tipTransport, const std::string &tipPass)
{
    if(tipTransport=="Metro")
    {
        if(tipPass=="Zi")
        {
            if(getFonduri()<5*0.8)
            {
                std::cout<<"Fonduri insuficiente\n";
                return;
            }
            setFonduri(getFonduri()-5*0.8);
            setBileteMetro(getBileteMetro()+2);
            std::cout<<"Abonament Metro cumparat pentru o zi\n";
        }
        else if(tipPass=="Saptamana")
        {
            if(getFonduri()<20*0.8)
            {
                std::cout<<"Fonduri insuficiente\n";
                return;
            }
            setFonduri(getFonduri()-20*0.8);
            setBileteMetro(getBileteMetro()+14);
            std::cout<<"Abonament Metro cumparat pentru o saptamana\n";
        }
        else if(tipPass=="Luna")
        {
            if(getFonduri()<50*0.8)
            {
                std::cout<<"Fonduri insuficiente\n";
                return;
            }
            setFonduri(getFonduri()-50*0.8);
            setBileteMetro(getBileteMetro()+60);
            std::cout<<"Abonament Metro cumparat pentru o luna\n";
        }
        else
        {
            std::cout<<"Tip de abonament invalid\n";
        }
    }
    else if(tipTransport=="Bus")
    {
        if(tipPass=="Zi")
        {
            if(getFonduri()<3*0.8)
            {
                std::cout<<"Fonduri insuficiente\n";
                return;
            }
            setFonduri(getFonduri()-5*0.8);
            setBileteBus(getBileteBus()+2);
            std::cout<<"Abonament Bus cumparat pentru o zi\n";
        }
        else if(tipPass=="Saptamana")
        {
            if(getFonduri()<10*0.8)
            {
                std::cout<<"Fonduri insuficiente\n";
                return;
            }
            setFonduri(getFonduri()-10*0.8);
            setBileteBus(getBileteBus()+14);
            std::cout<<"Abonament Bus cumparat pentru o saptamana\n";
        }
        else if(tipPass=="Luna")
        {
            if(getFonduri()<30*0.8)
            {
                std::cout<<"Fonduri insuficiente\n";
                return;
            }
            setFonduri(getFonduri()-30*0.8);
            setBileteBus(getBileteBus()+60);
            std::cout<<"Abonament Bus cumparat pentru o luna\n";
        }
        else
        {
            std::cout<<"Tip de abonament invalid\n";
        }
    }
    else
    {
        std::cout<<"Tip de transport invalid\n";
    }
}