#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <termios.h> // For termios, tcsetattr, tcgetattr
#include <unistd.h>  // For STDIN_FILENO
std::ofstream g("clienti.txt", std::ios::app);
// class Portofel;
class Client;
class Portofel
{
    int fonduri;
    //bilete_abonamente *Achizitii;
    bool are_bilet;
    bool are_abonament;
    std::string tip_abonament;

public:
    Portofel(int fonduri = 0, bool are_bilet=false, bool are_abonament=false, std::string tip_abonament="Nu are abonament normal")
    {
        this->fonduri = fonduri;
        this->are_bilet=are_bilet;
        this->are_abonament=are_abonament;
        this->tip_abonament=tip_abonament;
    }
    Portofel(const Portofel &portofel)
    {
        this->fonduri = portofel.fonduri;
        this->are_bilet=portofel.are_bilet;
        this->are_abonament=portofel.are_abonament;
        this->tip_abonament=portofel.tip_abonament;
    }
    ~Portofel()
    {
    }
    //getter
    int getFonduri() const { return fonduri; }
    bool getAreBilet() const { return are_bilet; }
    bool getAreAbonament() const { return are_abonament; }
    std::string getTipAbonament() const { return tip_abonament; }
    // setter
    void setFonduri(int fonduri)
    {
        this->fonduri = fonduri;
    }
    void depunere(int suma)
    {
        this->fonduri += suma;
    }

    void afisareFonduri(const Client& client) const;
    
    
};
/*
std::string getTipAbonamentSpecial(const Client &client)
{
    return client.getCaz();
}
*/
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
    Client(std::string nume, std::string prenume, std::string password,std::string id, bool are_abonament, Portofel portofel, bool caz_special, std::string caz = "Nu se incadreaza in niciun caz special")
    {
        this->nume = nume;
        this->prenume = prenume;
        this->password = password;
        this->id = id;
        this->are_abonament = are_abonament;
        this->portofel = portofel;
        this->caz_special = caz_special;
        this->caz=caz;
        std::cout << "Contul a fost creat cu succes!\n";
    }
    Client(const Client &client)
    {
        this->nume = client.nume;
        this->prenume = client.prenume;
        this->password = client.password;
        this->id = client.id;
        this->are_abonament = client.are_abonament;
        this->portofel = client.portofel;
        this->caz_special = client.caz_special;
        this->caz=client.caz;
    }
    std::string getNume() const { return nume; }
    std::string getPrenume() const { return prenume; }
    std::string getPassword() const { return password; }
    std::string getId() const { return id; }
    bool getAreAbonament() const { return are_abonament; }
    bool getCazSpecial() const { return caz_special; }
    std::string getCaz() const { return caz; }

    Portofel getPortofel() const { return portofel; }
    int getFonduri() const { return portofel.getFonduri(); }
    bool getAreBilet() const { return portofel.getAreBilet(); }
    bool getAreAbonamentPortofel() const { return portofel.getAreAbonament(); }  // Avoids name conflict
    std::string getTipAbonament() const { return portofel.getTipAbonament(); }
    void afisare() const
    {
        std::cout << "Client: " << nume << " " << prenume << "\n";
        std::cout << "ID: " << id << "\n";
        std::cout << "Abonament: " << (are_abonament ? "Da" : "Nu") << "\n";
        std::cout << "Caz special: " << (caz_special ? "Da" : "Nu") << "\n";
        portofel.afisareFonduri(*this);
    }
    ~Client() {}
    friend std::string generateID(const std::string &nume, const std::string &prenume);
    //friend std::ofstream& operator<<(std::ofstream& os, const Client& client);
    friend std::string getTipAbonamentSpecial(const Client &client);
};
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
void Portofel::afisareFonduri(const Client& client) const
{
    std::cout << "Fonduri disponibile: " << this->fonduri << " RON\n";
    std::cout << "Bilet: " << (this->are_bilet ? "Da" : "Nu") << "\n";
    std::cout << "Abonament: " << (this->are_abonament ? "Da" : "Nu") << "\n";
    std::cout << "Tip abonament: " << this->tip_abonament << "\n";
    std::cout << "Tip abonament special: " << client.getCaz() << "\n";
}
std::string getHiddenPassword() {
    std::cout << "Creati parola pentru contul dumneavoastra:" << std::endl;

    // Save current terminal settings.
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    // Turn off ECHO and canonical mode (character-by-character input)
    newt.c_lflag &= ~(ECHO | ICANON);
    newt.c_cc[VMIN] = 1;  // minimum number of characters to read
    newt.c_cc[VTIME] = 0; // no timeout
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    std::string password;
    char ch;
    while (true) {
        // Use read() to get one character from standard input
        if (read(STDIN_FILENO, &ch, 1) != 1)
            break;
        
        if (ch == '\n' || ch == '\r') {
            std::cout << std::endl;
            break;
        }
        else if (ch == 127 || ch == '\b') {  // handle backspace (127 or '\b')
            if (!password.empty()) {
                password.pop_back();
                // Move cursor back, overwrite the character with space, and move back again.
                std::cout << "\b \b";
                std::cout.flush();
            }
        }
        else {
            password.push_back(ch);
            std::cout << '*';
            std::cout.flush();
        }
    }

    // Restore original terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return password;
}
int main()
{
    const int bilet_metro = 5;
    const int bilet_suprafata = 3;
    const int abonament_metro_luna = 100;
    const int abonament_metro_saptamana = 30;
    const int abonament_metro_zi = 10;
    const int abonament_suprafata = 50;
    const int abonament_special_metro=10;
    const int abonament_special_suprafata=5;
    std::vector<Client *> clienti;
    bool exit=false;
    while(!exit)
    {
    std::string raspuns;
    std::cout << "Ai cont?\n";
    std::cin >> raspuns;
    if (raspuns == "Nu")
    {
        std::cout << "Introduceti numele\n";
        std::string nume, prenume;
        std::cin >> nume;
        std::cout << "Introduceti prenumele\n";
        std::cin >> prenume;
        //std::cout<<"Creati parola pentru contul dumneavoastra:\n";
        std::string pass = getHiddenPassword();
        //std::cout << "Parola dumneavoastra: " << pass << std::endl;
        std::string id = generateID(nume, prenume);
        std::cout << "ID-ul dumneavoastra este: " << id << "\n";
        std::cout << "Ai abonament?\n"
                  << "Da/Nu\n";
        bool areAbonament;
        std::string are_abonament;
        std::cin >> are_abonament;
        if (are_abonament == "Da")
            areAbonament = true;
        else
            areAbonament = false;
        Portofel portofel;
        bool caz_special;
        std::string caz_special_string, da_nu;
        std::cout << "Te incadrezi intr-un caz special?\n";
        std::cout << "Introduceti 'Da' sau 'Nu'\n";
        std::cin >> da_nu;
        if (da_nu == "Da")
            caz_special = true;
        else
            caz_special = false;
        int caz=0;
        //std::string caz_special_string;
        if(caz_special==true)
        {
            std::cout<<"Introduceti cazul special in care va incadrati:\n";
            std::cout<<"1. Elev/Student\n";
            std::cout<<"2. Pensionar/persoana cu dizabilitati\n";
            std::cout<<"3. Salariat cu venitul minim pe economie\n";
            
            std::cin>>caz;

        }
        if(caz==0)
            caz_special_string="Nu se incadreaza in niciun caz special";
        else if(caz==1)
            caz_special_string="Elev/Student";
        else if(caz==2)
            caz_special_string="Pensionar/persoana cu dizabilitati";
        else if(caz==3)
            caz_special_string="Salariat cu venitul minim pe economie";
        std::cout << "Introduceti suma pe care doriti sa o depuneti in cont:\n";
        int suma;
        std::cin >> suma;
        portofel.setFonduri(suma);
        Client *client = new Client(nume, prenume, pass, id, areAbonament, portofel, caz_special,caz_special_string);
        client->afisare();
        g<<"Nume: "<<nume<<"\n";
        g<<"Prenume: "<<prenume<<"\n";
        g<<"ID: "<<id<<"\n";
        g<<"Abonament: "<<(areAbonament ? "Da" : "Nu")<<"\n";
        g<<"Caz special: "<<(caz_special ? "Da" : "Nu")<<"\n";
        g<<"Caz special: "<<caz_special_string<<"\n";
        g<<"Fonduri disponibile: "<<suma<<" RON\n"; //aici va trebui modificat, pentru ca isi poate depune si dupa
        //crearea contului
        clienti.push_back(client);
        std::cout<<"Continuati?\n";
        std::string continuare;
        std::cin>>continuare;
        if(continuare=="Nu")
            exit=true;
    }
    }
    if (!clienti.empty())
    {
        std::cout << "\nLista clientilor creati:\n";
        for (auto &client : clienti)
        {
            client->afisare();
        }
    }
    else
    {
        std::cout << "Niciun client inregistrat.\n";
    }
    return 0;
}

