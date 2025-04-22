#pragma once

#include <iostream>
#include <string>

// forward‐declare Client so we can mention it by reference
class Client;

class Portofel {
    int fonduri;
    bool are_bilet;
    bool are_abonament;
    std::string tip_abonament;

public:
    Portofel(int fonduri = 0,
             bool are_bilet = false,
             bool are_abonament = false,
             std::string tip_abonament = "Nu are abonament normal");

    
    int     getFonduri() const;
    bool    getAreBilet() const;
    bool    getAreAbonament() const;
    std::string getTipAbonament() const;
    void    setFonduri(int);
    void    depunere(int);
    void    set_are_bilet(bool);

    
    void afisareFonduri(const Client &client) const;
};