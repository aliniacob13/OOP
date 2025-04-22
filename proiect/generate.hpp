#pragma once
#include <iostream>
#include <string>
#include<fstream>
#include "Client.hpp"
#include "Portofel.hpp"
#include <termios.h> // pentru termios, tcsetattr, tcgetattr
#include <unistd.h>  // pentru STDIN_FILENO
std::string generateID(const std::string &nume, const std::string &prenume)
{
    std::string id = "";
    id = nume + prenume;
    int random_number_int = 0;
    srand(time(0));
    random_number_int = rand() % 1000 + 1;
    std::string random_number = std::to_string(random_number_int);
    id += random_number;
    return id;
}

std::string getHiddenPassword()
{
    std::cout << "Introduceti parola:" << std::endl;

    // salveaza setarile din terminal
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    // opreste modul echo si canonic
    newt.c_lflag &= ~(ECHO | ICANON);
    newt.c_cc[VMIN] = 1;  // nr minim caractere de citit
    newt.c_cc[VTIME] = 0; // no timeout
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    std::string password;
    char ch;
    while (true)
    {
        // folosim read() ca sa citim
        if (read(STDIN_FILENO, &ch, 1) != 1)
            break;

        if (ch == '\n' || ch == '\r')
        {
            std::cout << std::endl;
            break;
        }
        else if (ch == 127 || ch == '\b')
        { // backspace
            if (!password.empty())
            {
                password.pop_back();
                // muta cursorul inapoi, da overwrite si muta inapoi
                std::cout << "\b \b";
                std::cout.flush();
            }
        }
        else
        {
            password.push_back(ch);
            std::cout << '*';
            std::cout.flush();
        }
    }

    // reda setarile din terminal
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return password;
}