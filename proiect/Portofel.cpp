#pragma once
#include "Portofel.hpp"
#include "Client.hpp"   

Portofel::Portofel(int f, bool b, bool a, std::string t)
  : fonduri(f), are_bilet(b), are_abonament(a), tip_abonament(std::move(t))
{}

int Portofel::getFonduri() const                { return fonduri; }
bool Portofel::getAreBilet() const              { return are_bilet; }
bool Portofel::getAreAbonament() const          { return are_abonament; }
std::string Portofel::getTipAbonament() const   { return tip_abonament; }
void Portofel::setFonduri(int f)                { fonduri = f; }
void Portofel::depunere(int s)                  { fonduri += s; }
void Portofel::set_are_bilet(bool b)            { are_bilet = b; }

void Portofel::afisareFonduri(const Client &client) const {
    std::cout << "Fonduri disponibile: " << fonduri << " RON\n";
    std::cout << "Bilet: "            << (are_bilet       ? "Da" : "Nu") << "\n";
    std::cout << "Abonament: "       << (are_abonament   ? "Da" : "Nu") << "\n";
    std::cout << "Tip abonament: "   << tip_abonament              << "\n";
    std::cout << "Tip abonament special: " << client.getCaz()       << "\n";
}
