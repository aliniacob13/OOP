#include<iostream>
#include<string>
#include<vector>
//class Portofel;
class Portofel
{
    int fonduri;
    public:
        Portofel(int fonduri=0)
        {
            this->fonduri=fonduri;
        }
        Portofel(const Portofel& portofel)
        {
            this->fonduri=portofel.fonduri;
        }
        ~Portofel(){}
        //getter
        int getFonduri()
        {
            return this->fonduri;
        }
        //setter
        void setFonduri(int fonduri)
        {
            this->fonduri=fonduri;
        }
        void depunere(int suma) {
            this->fonduri += suma;
        }
    
        void afisareFonduri() const {
            std::cout << "Fonduri disponibile: " << fonduri << " RON\n";
        }
};
class Client
{
    std::string nume;
    std::string prenume;
    std::string id;
    bool are_abonament;
    Portofel portofel;
    bool caz_special;
    public:
        Client(std::string nume, std::string prenume, std::string id, bool are_abonament, Portofel portofel, bool caz_special)
        {
            this->nume=nume;
            this->prenume=prenume;
            this->id=id;
            this->are_abonament=are_abonament;
            this->portofel=portofel;
            this->caz_special=caz_special;
            std::cout<<"Contul a fost creat cu succes!\n";
        }
        Client(const Client& client)
        {
            this->nume=client.nume;
            this->prenume=client.prenume;
            this->id=client.id;
            this->are_abonament=client.are_abonament;
            this->portofel=client.portofel;
            this->caz_special=client.caz_special;
        }
        void afisare() const {
            std::cout << "Client: " << nume << " " << prenume << "\n";
            std::cout << "ID: " << id << "\n";
            std::cout << "Abonament: " << (are_abonament ? "Da" : "Nu") << "\n";
            std::cout << "Caz special: " << (caz_special ? "Da" : "Nu") << "\n";
            portofel.afisareFonduri();
        }
        ~Client(){}
};

int main()
{
    std::vector<Client> clienti;
    std::string raspuns;
    std::cout<<"Ai cont?\n";
    std::cin>>raspuns;
    if(raspuns=="Nu")
    {
        std::cout<<"Introduceti numele\n";
        std::string nume, prenume;
        std::cin>>nume;
        std::cout<<"Introduceti prenumele\n";
        std::cin>>prenume;
        std::cout<<"Introduceti id-ul\n";
        std::string id;
        std::cin>>id;
        std::cout<<"Ai abonament?\n";
        bool areAbonament;
        std::string are_abonament;
        std::cin>>are_abonament;
        if(are_abonament=="Da")
            areAbonament=true;
        else
            areAbonament=false;
        Portofel portofel;
        bool caz_special;
        std::string caz_special_string, da_nu;
        std::cout<<"Ai caz special?\n";
        std::cout<<"Introduceti 'Da' sau 'Nu'\n";
        std::cin>>da_nu;
        if(da_nu=="Da")
            caz_special=true;
        else
            caz_special=false;
        std::cout<<"Introduceti suma pe care doriti sa o depuneti in cont:\n";
        int suma;
        std::cin>>suma;
        portofel.setFonduri(suma);
        Client client(nume, prenume, id, areAbonament, portofel, caz_special);
        client.afisare();
        clienti.push_back(client);
    }
    if (!clienti.empty()) {
        std::cout << "\nLista clientilor creati:\n";
        for (auto& client : clienti) {
            client.afisare();
        }
    } else {
        std::cout << "Niciun client inregistrat.\n";
    }
    return 0;
}
