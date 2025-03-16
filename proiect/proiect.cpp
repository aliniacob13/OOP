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
class staff
{
    const std::string nume;
    const std::string prenume;
    const std::string email;
    const std::string password;
    const std::string pozitie;

public:
    staff(const std::string &nume, const std::string &prenume, const std::string &email, const std::string &password, const std::string &pozitie) : nume(nume), prenume(prenume), email(email), password(password), pozitie(pozitie) {}
    staff(const staff &other) : nume(other.nume), prenume(other.prenume), email(other.email), password(other.password), pozitie(other.pozitie) {}
    ~staff() {}
    std::string getNume() const { return nume; }
    std::string getPrenume() const { return prenume; }
    std::string getEmail() const { return email; }
    std::string getPassword() const { return password; }
    std::string getPozitie() const { return pozitie; }
    /// i need to add a function that can change the password(cu pointeri ca sa pot distruge bariera de protectie)
    /// vezi curs paun ca sa vezi cum se face
};
class mijloc_transport
{
    const std::string tip;
    //const int pret;
    const int pret_bilet;
    const int pret_abonament_zi;
    const int pret_abonament_saptamana;
    const int pret_abonament_luna;

public:
    mijloc_transport(const std::string &t, const int &p, const int &pz, const int &ps, const int &pl) : tip(t), pret_bilet(p), pret_abonament_zi(pz), pret_abonament_saptamana(ps), pret_abonament_luna(pl)  {}             // Constructor
    mijloc_transport(const mijloc_transport &other) : tip(other.tip), pret_bilet(other.pret_bilet), pret_abonament_zi(other.pret_abonament_zi), pret_abonament_saptamana(other.pret_abonament_saptamana), pret_abonament_luna(other.pret_abonament_luna) {} // Copy constructor
    ~mijloc_transport()
    {
        // nu stiu daca trebuie sa pun ceva aici
    }
    std::string getTip() const { return tip; }
    int getPretBilet() const { return pret_bilet; }
};
class Client;
class Portofel
{
    int fonduri;
    // bilete_abonamente *Achizitii;
    bool are_bilet;
    bool are_abonament;
    std::string tip_abonament;

public:
    Portofel(int fonduri = 0, bool are_bilet = false, bool are_abonament = false, std::string tip_abonament = "Nu are abonament normal")
    {
        this->fonduri = fonduri;
        this->are_bilet = are_bilet;
        this->are_abonament = are_abonament;
        this->tip_abonament = tip_abonament;
    }
    Portofel(const Portofel &portofel)
    {
        this->fonduri = portofel.fonduri;
        this->are_bilet = portofel.are_bilet;
        this->are_abonament = portofel.are_abonament;
        this->tip_abonament = portofel.tip_abonament;
    }
    ~Portofel()
    {
    }
    // getter
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

    void afisareFonduri(const Client &client) const;
};

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
    Client(std::string nume, std::string prenume, std::string password, std::string id, bool are_abonament, Portofel portofel, bool caz_special, std::string caz = "Nu se incadreaza in niciun caz special")
    {
        this->nume = nume;
        this->prenume = prenume;
        this->password = password;
        this->id = id;
        this->are_abonament = are_abonament;
        this->portofel = portofel;
        this->caz_special = caz_special;
        this->caz = caz;
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
        this->caz = client.caz;
    }
    //settere
    void set_password(std::string password){
        this->password=password;
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
    bool getAreAbonamentPortofel() const { return portofel.getAreAbonament(); } // Avoids name conflict
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
    void depunere(int suma) {
        portofel.depunere(suma);
    }
    friend std::string generateID(const std::string &nume, const std::string &prenume);
    // friend std::ofstream& operator<<(std::ofstream& os, const Client& client);
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
void Portofel::afisareFonduri(const Client &client) const
{
    std::cout << "Fonduri disponibile: " << this->fonduri << " RON\n";
    std::cout << "Bilet: " << (this->are_bilet ? "Da" : "Nu") << "\n";
    std::cout << "Abonament: " << (this->are_abonament ? "Da" : "Nu") << "\n";
    std::cout << "Tip abonament: " << this->tip_abonament << "\n";
    std::cout << "Tip abonament special: " << client.getCaz() << "\n";
}
std::string getHiddenPassword()
{
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
    while (true)
    {
        // Use read() to get one character from standard input
        if (read(STDIN_FILENO, &ch, 1) != 1)
            break;

        if (ch == '\n' || ch == '\r')
        {
            std::cout << std::endl;
            break;
        }
        else if (ch == 127 || ch == '\b')
        { // handle backspace (127 or '\b')
            if (!password.empty())
            {
                password.pop_back();
                // Move cursor back, overwrite the character with space, and move back again.
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

    // Restore original terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return password;
}
int main()
{
    // o sa trebuiasca sa elimin aceste const-uri
    const int bilet_metro = 5;
    const int bilet_suprafata = 3;
    const int abonament_metro_luna = 100;
    const int abonament_metro_saptamana = 30;
    const int abonament_metro_zi = 10;
    const int abonament_suprafata = 50;
    const int abonament_special_metro = 10;
    const int abonament_special_suprafata = 5;
    mijloc_transport metro("Metro", 5, 10, 30, 100);
    mijloc_transport tramvai("Tramvai", 3, 7, 25, 70);
    mijloc_transport autobuz("Autobuz", 4, 10, 27, 65);
    std::cout << "Pretul unui bilet de tramvai este: " << tramvai.getPretBilet() << " RON\n";
    std::vector<Client *> clienti;
    std::vector<staff *> angajati;
    bool exit = false;
    std::cout << "Bun venit la aplicatia de transport!\n";
    staff boss("Andrei", "Paun", "apaun@yahoo.com", "1234", "Manager");
    while (!exit)
    {
        std::cout << "Client/Staff?\n";
        std::string client_staff;
        std::cin >> client_staff;
        if (client_staff == "Client")
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
                // std::cout<<"Creati parola pentru contul dumneavoastra:\n";
                std::string pass = getHiddenPassword();
                // std::cout << "Parola dumneavoastra: " << pass << std::endl;
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
                    {
                        caz_special = true;
                        std::cout<<"Trebuie sa mergeti la o casa de bilete pentru a va face abonamentul special.\n";
                    }
                else
                    caz_special = false;
                int caz = 0;
                // std::string caz_special_string;

                // if (caz_special == true)
                // {
                //     std::cout << "Introduceti cazul special in care va incadrati:\n";
                //     std::cout << "1. Elev/Student\n";
                //     std::cout << "2. Pensionar/persoana cu dizabilitati\n";
                //     std::cout << "3. Salariat cu venitul minim pe economie\n";

                //     std::cin >> caz;
                // }
                // if (caz == 1)
                //     caz_special_string = "Elev/Student";
                // else if (caz == 2)
                //     caz_special_string = "Pensionar/persoana cu dizabilitati";
                // else if (caz == 3)
                //     caz_special_string = "Salariat cu venitul minim pe economie";
                std::cout << "Introduceti suma pe care doriti sa o depuneti in cont:\n";
                int suma;
                std::cin >> suma;
                portofel.setFonduri(suma);
                Client *client = new Client(nume, prenume, pass, id, areAbonament, portofel, caz_special); //caz_special_string ia val. default
                client->afisare();
                g << "Nume: " << nume << "\n";
                g << "Prenume: " << prenume << "\n";
                g << "ID: " << id << "\n";
                g << "Abonament: " << (areAbonament ? "Da" : "Nu") << "\n";
                g << "Caz special: " << (caz_special ? "Da" : "Nu") << "\n";
                g << "Caz special: " << caz_special_string << "\n";
                g << "Fonduri disponibile: " << suma << " RON\n"; // aici va trebui modificat, pentru ca isi poate depune si dupa
                // crearea contului
                clienti.push_back(client);
            }
        }
        else
        {
            std::cout << "Sign in\n";
            std::string email, password;
            std::string nume, prenume;
            std::cout << "Nume: ";
            std::cin >> nume;
            std::cout << "Prenume: ";
            std::cin >> prenume;
            std::cout << "Email: ";
            std::cin >> email;
            std::cout << "Password: ";
            std::cin >> password;
            bool found = false;
            std::string prenume_nume;
            prenume_nume = prenume + " " + nume;
            // std::cout<<prenume_nume;
            if (prenume_nume == "Andrei Paun")
            {
                bool iesire_sesiune = false;
                if (boss.getEmail() == email && boss.getPassword() == password)
                {
                    found = true;
                }
                if (found == true)
                {
                    std::cout << "Logare reusita!\n";
                    std::cout << "Bine ati venit, domnule Paun!\n";
                    bool logout = false;
                    while (!logout)
                    {
                        std::cout << "Ce doriti sa faceti?\n";
                        std::cout << "1. Adaugare angajat\n";
                        std::cout << "2. Stergere angajat\n";
                        std::cout << "3. Afisare angajat(i)\n";
                        std::cout << "4. Modificare date angajat\n";
                        std::cout << "5. Logout\n";
                        int raspuns;
                        std::cin >> raspuns;
                        if (raspuns == 1)
                        {
                            std::string nume, prenume, email, password, pozitie;
                            std::cout << "Nume: ";
                            std::cin >> nume;
                            std::cout << "Prenume: ";
                            std::cin >> prenume;
                            std::cout << "Email: ";
                            std::cin >> email;
                            std::cout << "Password: ";
                            std::cin >> password;
                            std::cout << "Pozitie: ";
                            std::cin >> pozitie;
                            staff *angajat = new staff(nume, prenume, email, password, pozitie);
                            angajati.push_back(angajat);
                            std::cout << "Angajatul a fost adaugat cu succes!\n";
                        }
                        else if (raspuns == 2)
                        {
                            std::string numeStergere;
                            std::cout << "Introdu numele angajatului de sters: ";
                            std::cin >> numeStergere;

                            bool found_angajat = false;
                            for (auto it = angajati.begin(); it != angajati.end(); ++it)
                            {
                                if ((*it)->getNume() == numeStergere)
                                {
                                    delete *it;         //Elibereaza memoria
                                    angajati.erase(it); //Sterge din vectorul de angajati
                                    std::cout << "Angajat sters!\n";
                                    found_angajat = true;
                                    break;
                                }
                            }
                            if (!found_angajat)
                            {
                                std::cout << "Angajatul cu numele " << numeStergere << " nu a fost gasit.\n";
                            }
                        }
                        else if(raspuns==3)
                        {
                            std::cout<<"Pe cine doriti sa afisati?\n";
                            std::cout<<"1. Toti angajatii\n";
                            std::cout<<"2. Un angajat\n";
                            int raspuns_afisare;
                            std::cin>>raspuns_afisare;
                            if(raspuns_afisare==1)
                            {
                                for(auto &angajat:angajati)
                                {
                                    std::cout<<"Nume: "<<angajat->getNume()<<"\n";
                                    std::cout<<"Prenume: "<<angajat->getPrenume()<<"\n";
                                    std::cout<<"Email: "<<angajat->getEmail()<<"\n";
                                    std::cout<<"Pozitie: "<<angajat->getPozitie()<<"\n";
                                }
                            }
                            else if(raspuns_afisare==2)
                            {
                                std::string numeAfisare;
                                std::cout<<"Introduceti numele angajatului pe care doriti sa il afisati: ";
                                std::cin>>numeAfisare;
                                bool found_angajat=false;
                                for(auto &angajat:angajati)
                                {
                                    if(angajat->getNume()==numeAfisare)
                                    {
                                        std::cout<<"Nume: "<<angajat->getNume()<<"\n";
                                        std::cout<<"Prenume: "<<angajat->getPrenume()<<"\n";
                                        std::cout<<"Email: "<<angajat->getEmail()<<"\n";
                                        std::cout<<"Pozitie: "<<angajat->getPozitie()<<"\n";
                                        found_angajat=true;
                                        break;
                                    }
                                }
                                if(!found_angajat)
                                {
                                    std::cout<<"Angajatul cu numele "<<numeAfisare<<" nu a fost gasit.\n";
                                }
                            }
                        }
                        else if(raspuns==5)
                        {
                            logout=true;
                        }
                        if(logout==true)
                        {
                            std::cout<<"Ati iesit din sesiune!\n";
                        }
                    }
                }
                else
                {
                    std::cout << "Logare nereusita!\n";
                    std::cout << "Email sau parola gresita!\n";
                }
            }
            else
            {   
                bool found_angajat=false;
                for(auto &angajati:angajati)
                {
                    if(angajati->getEmail()==email && angajati->getPassword()==password)
                    {
                        found_angajat=true;
                    }
                    
                }
                if(found_angajat==true)
                {
                    std::cout<<"Logare reusita!\n";
                    std::cout<<"Ce actiune doriti sa efectuati?\n";
                    std::cout<<"1. Incarcare cont cu fonduri\n";
                    std::cout<<"2. Incarcare cont cu abonament\n";
                    std::cout<<"3. Incarcare cont caz special\n";
                    std::cout<<"4.Schimbare parola cont utilizator\n";
                    int actiune;
                    std::cin>>actiune;
                    if(actiune==1)
                    {
                        std::string id, password;
                        std::cout<<"Introduceti ID-ul clientului: ";
                        std::cin>>id;
                        std::cout<<"Introduceti parola: ";
                        password=getHiddenPassword();
                        bool found_client=false;
                        for (auto &client : clienti) {
                            if (client->getId() == id && client->getPassword() == password) {
                                found_client = true;
                                std::cout << "Client gasit!\n";
                                std::cout << "Introduceti suma pe care doriti sa o depuneti in cont: ";
                                int suma;
                                std::cin >> suma;
                        
                                
                                client->depunere(suma);
                        
                                std::cout << "Suma a fost depusa cu succes!\n";
                                client->afisare();
                            }
                        }
                    }
                    else if(actiune==4)
                    {
                        std::string id, password;
                        std::cout<<"Introduceti ID-ul clientului: ";
                        std::cin>>id;
                        
                        bool found_client=false;
                        for (auto &client : clienti) {
                            if (client->getId() == id) {
                                found_client = true;
                                //ce urmeaza sa fac(adica ce as dori sa fac): sparg bariera de protectie const(NU MERGE)
                                std::cout << "Client gasit!\n";
                                std::cout << "Introduceti noua parola: ";
                                std::string new_password=getHiddenPassword();
                                client->set_password(new_password);
                                std::cout << "Parola a fost schimbata cu succes!\n";
                                client->afisare();
                            }
                        }
                    }
                    else
                    {
                        std::cout<<"Actiune nerecunoscuta!\n";
                    }
                }
            }
        }
        std::cout << "Continuati?\n";
        std::string continuare;
        std::cin >> continuare;
        if (continuare == "Nu")
            exit = true;
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
