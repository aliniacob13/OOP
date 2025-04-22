#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <regex>
std::ofstream h("angajati.txt", std::ios::app);
class staff
{
    std::string nume;
    std::string prenume;
    char *email;
    char *password;
    char *pozitie;

public:
    staff(const std::string &nume, const std::string &prenume,
          const std::string &emailStr, const std::string &passwordStr,
          const std::string &pozitieStr) : nume(nume), prenume(prenume)
    {
        email = new char[emailStr.size() + 1];
        std::strcpy(email, emailStr.c_str());
        password = new char[passwordStr.size() + 1];
        std::strcpy(password, passwordStr.c_str());
        pozitie = new char[pozitieStr.size() + 1];
        std::strcpy(pozitie, pozitieStr.c_str());
    }
    staff(const staff &other)
        : nume(other.nume), prenume(other.prenume)
    {
        email = new char[std::strlen(other.email) + 1];
        std::strcpy(email, other.email);
        password = new char[std::strlen(other.password) + 1];
        std::strcpy(password, other.password);
        pozitie = new char[std::strlen(other.pozitie) + 1];
        std::strcpy(pozitie, other.pozitie);
    }
    ~staff()
    {
        delete[] email;
        delete[] password;
        delete[] pozitie;
    }
    std::string getNume() const { return nume; }
    std::string getPrenume() const { return prenume; }
    std::string getEmail() const { return email; }
    std::string getPassword() const { return password; }
    std::string getPozitie() const { return pozitie; }

    void set_nume(const std::string &new_nume)
    {
        nume = new_nume;
    }
    void set_prenume(const std::string &new_prenume)
    {
        prenume = new_prenume;
    }
    void set_password(const std::string &new_password)
    {
        delete[] password;
        password = new char[new_password.size() + 1];
        std::strcpy(password, new_password.c_str());
    }
    void set_pozitie(const std::string &new_pozitie)
    {
        delete[] pozitie; // elibereaza memoria veche
        pozitie = new char[new_pozitie.size() + 1];
        std::strcpy(pozitie, new_pozitie.c_str());
    }
    void set_email(const std::string &new_email)
    {
        delete[] email; // elibereaza memoria veche
        email = new char[new_email.size() + 1];
        std::strcpy(email, new_email.c_str());
    }
    friend std::ostream &operator<<(std::ostream &, const staff &);
    // friend std::istream& operator>>(std::istream&, staff&);
    void afisare_staff(staff s)
    {
        std::cout << s;
    }
    friend std::istream &operator>>(std::istream &, staff *&);
};
std::istream &operator>>(std::istream &is, staff *&employee)
{
    std::string nume, prenume, email, password, pozitie;

    std::cout << "Introduceti numele:\n";
    is >> nume;

    std::cout << "Introduceti prenumele:\n";
    is >> prenume;

    std::cout << "Introduceti email-ul:\n";
    is >> email;
    std::regex email_pattern("^[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\\.[a-zA-Z0-9-.]+$");
    while (!std::regex_match(email, email_pattern))
    {
        std::cout << "Email invalid! Introduceti un email valid:\n";
        is >> email;
    }

    std::cout << "Introduceti parola:\n";
    is >> password;

    std::cout << "Introduceti pozitia:\n";
    is >> pozitie;

    // creaza obiect dinamic
    employee = new staff(nume, prenume, email, password, pozitie);

    h << *employee;
    h.flush();

    return is;
}
std::ostream &operator<<(std::ostream &stream, const staff &s)
{
    stream << "Nume: " << s.nume << "\n";
    stream << "Prenume: " << s.prenume << "\n";
    stream << "Email: " << s.email << "\n";
    stream << "Password: " << s.password << "\n";
    stream << "Pozitie: " << s.pozitie << "\n";
    return stream;
}
