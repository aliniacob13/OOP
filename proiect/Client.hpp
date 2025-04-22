// Client.hpp
#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include "Portofel.hpp"
#include "generate.hpp"

extern std::ofstream g;

class Client
{
    std::string nume;
    std::string prenume;
    std::string password;
    std::string id;
    bool are_abonament;
    Portofel portofel;
    bool caz_special;
    std::string caz;

public:
    Client(std::string nume,
           std::string prenume,
           std::string password,
           std::string id,
           bool are_abonament,
           Portofel portofel,
           bool caz_special = false,
           std::string caz = "Nu se incadreaza in niciun caz special");

    Client(const Client &client);

    // setters
    void set_password(std::string password);
    void set_id(std::string id);
    void set_are_abonament(bool are_abonament);
    void set_caz_special(bool caz_special);
    void set_caz(std::string caz);

    // getters
    std::string getNume() const;
    std::string getPrenume() const;
    std::string getPassword() const;
    std::string getId() const;
    bool        getAreAbonament() const;
    bool        getCazSpecial() const;
    std::string getCaz() const;

    Portofel &getPortofel();
    int        getFonduri() const;
    bool       getAreBilet() const;
    bool       getAreAbonamentPortofel() const;
    std::string getTipAbonament() const;

    void afisare() const;
    void depunere(int suma);

    // give a ticket and deduct from funds
    Client &operator+=(int bilet);

    // friends
    friend std::string generateID(const std::string &nume, const std::string &prenume);
    friend std::string getTipAbonamentSpecial(const Client &client);
    friend std::ostream &operator<<(std::ostream &os, const Client &client);
    friend std::istream &operator>>(std::istream &is, Client *&client);

    ~Client() {}
};