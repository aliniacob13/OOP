#pragma once
#include "Client.hpp"

std::ofstream g("clienti.txt", std::ios::app);

Client::Client(std::string nume,
               std::string prenume,
               std::string password,
               std::string id,
               bool are_abonament,
               Portofel portofel,
               bool caz_special,
               std::string caz)
{
    this->nume = std::move(nume);
    this->prenume = std::move(prenume);
    this->password = std::move(password);
    this->id = std::move(id);
    this->are_abonament = are_abonament;
    this->portofel = std::move(portofel);
    this->caz_special = caz_special;
    this->caz = std::move(caz);
    // std::cout << "Contul a fost creat cu succes!\n";
}

Client::Client(const Client &client)
{
    this->nume = client.nume;
    this->prenume = client.prenume;
    this->password = client.password;
    this->id = client.id;
    this->are_abonament = client.are_abonament;
    this->portofel = client.portofel;
    this->caz_special = client.caz_special;
    this->caz = client.caz;
}


void Client::set_password(std::string pw) { password = std::move(pw); }
void Client::set_id(std::string i) { id = std::move(i); }
void Client::set_are_abonament(bool a) { are_abonament = a; }
void Client::set_caz_special(bool cs) { caz_special = cs; }
void Client::set_caz(std::string c) { caz = std::move(c); }


std::string Client::getNume() const { return nume; }
std::string Client::getPrenume() const { return prenume; }
std::string Client::getPassword() const { return password; }
std::string Client::getId() const { return id; }
bool Client::getAreAbonament() const { return are_abonament; }
bool Client::getCazSpecial() const { return caz_special; }
std::string Client::getCaz() const { return caz; }

Portofel &Client::getPortofel() { return portofel; }
int Client::getFonduri() const { return portofel.getFonduri(); }
bool Client::getAreBilet() const { return portofel.getAreBilet(); }
bool Client::getAreAbonamentPortofel() const { return portofel.getAreAbonament(); }
std::string Client::getTipAbonament() const { return portofel.getTipAbonament(); }

void Client::afisare() const
{
    std::cout << "Client: " << nume << " " << prenume << "\n"
              << "ID: " << id << "\n"
              << "Abonament: " << (are_abonament ? "Da" : "Nu") << "\n"
              << "Caz special: " << (caz_special ? "Da" : "Nu") << "\n";
    portofel.afisareFonduri(*this);
}

void Client::depunere(int suma)
{
    portofel.depunere(suma);
}

Client &Client::operator+=(int bilet)
{
    portofel.set_are_bilet(true);
    portofel.setFonduri(portofel.getFonduri() - bilet);
    return *this;
}


std::ostream &operator<<(std::ostream &stream, const Client &c)
{
    stream << "Nume: " << c.nume << "\n"
           << "Prenume: " << c.prenume << "\n"
           << "ID: " << c.id << "\n"
           << "Password: " << c.password << "\n"
           << "Caz special: " << (c.caz_special ? "Da" : "Nu") << "\n"
           << "Descriere caz special: " << c.caz << "\n"
           << "Fonduri disponibile: " << c.portofel.getFonduri() << " RON\n"
           << "Bilet: " << (c.portofel.getAreBilet() ? "Da" : "Nu") << "\n"
           << "Abonament (portofel): " << (c.portofel.getAreAbonament() ? "Da" : "Nu") << "\n"
           << "Tip abonament: " << c.portofel.getTipAbonament() << "\n";
    return stream;
}

// read interactively, then append to file
std::istream &operator>>(std::istream &is, Client *&client)
{
    std::string nume, prenume;
    std::cout << "Introduceti numele\n";
    is >> nume;
    std::cout << "Introduceti prenumele\n";
    is >> prenume;

    std::string pass = getHiddenPassword();
    std::string id = generateID(nume, prenume);
    std::cout << "ID-ul dumneavoastra este: " << id << "\n";

    bool abonament = false;
    Portofel portofel;
    bool caz_special = false;
    std::string da_nu;
    std::cout << "Te incadrezi intr-un caz special?\n";
    while (da_nu != "Da" && da_nu != "Nu")
    {
        std::cout << "Introduceti 'Da' sau 'Nu'\n";
        is >> da_nu;
    }
    if (da_nu == "Da")
    {
        caz_special = true;
        std::cout << "Trebuie sa mergeti la o casa de bilete pentru a va face abonamentul special.\n";
    }

    std::cout << "Introduceti suma pe care doriti sa o depuneti in cont:\n";
    int suma = -3;
    while (suma < 0)
    {
        is >> suma;
        if (suma < 0)
            std::cout << "Suma nu poate fi negativa. Introduceti o suma valida:\n";
    }
    portofel.setFonduri(suma);

    client = new Client(nume, prenume, pass, id, abonament, portofel, caz_special);
    g << *client;
    g.flush();
    return is;
}
