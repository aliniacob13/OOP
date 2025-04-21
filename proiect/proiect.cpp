#include <iostream>
#include <regex>
#include <string>
#include <vector>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <termios.h> // pentru termios, tcsetattr, tcgetattr
#include <unistd.h>  // pentru STDIN_FILENO
#include <cctype>   
std::ofstream g("clienti.txt", std::ios::app);
std::ofstream h("angajati.txt", std::ios::app);
// class Portofel;
std::string toLower(const std::string &s) {
    std::string result = s;
    for (int i = 0; i < result.size(); ++i) {
        result[i] = std::tolower(result[i]);
    }
    return result;
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

class mijloc_transport
{
    const std::string tip;
    // const int pret;
    const int pret_bilet;
    const int pret_abonament_zi;
    const int pret_abonament_saptamana;
    const int pret_abonament_luna;

public:
    mijloc_transport(const std::string &t, const int &p, const int &pz, const int &ps, const int &pl) : tip(t), pret_bilet(p), pret_abonament_zi(pz), pret_abonament_saptamana(ps), pret_abonament_luna(pl) {}                                              // Constructor
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
    void set_are_bilet(bool are_bilet)
    {
        this->are_bilet = are_bilet;
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
    Client(std::string nume, std::string prenume, std::string password, std::string id, bool are_abonament, Portofel portofel, bool caz_special = false, std::string caz = "Nu se incadreaza in niciun caz special")
    {
        this->nume = nume;
        this->prenume = prenume;
        this->password = password;
        this->id = id;
        this->are_abonament = are_abonament;
        this->portofel = portofel;
        this->caz_special = caz_special;
        this->caz = caz;
        // std::cout << "Contul a fost creat cu succes!\n";
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
    // settere
    void set_password(std::string password)
    {
        this->password = password;
    }
    void set_id(std::string id)
    {
        this->id = id;
    }
    void set_are_abonament(bool are_abonament)
    {
        this->are_abonament = are_abonament;
    }
    void set_caz_special(bool caz_special)
    {
        this->caz_special = caz_special;
    }
    void set_caz(std::string caz)
    {
        this->caz = caz;
    }
    // gettere
    std::string getNume() const { return nume; }
    std::string getPrenume() const { return prenume; }
    std::string getPassword() const { return password; }
    std::string getId() const { return id; }
    bool getAreAbonament() const { return are_abonament; }
    bool getCazSpecial() const { return caz_special; }
    std::string getCaz() const { return caz; }

    Portofel &getPortofel() { return portofel; }
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
    void depunere(int suma)
    {
        portofel.depunere(suma);
    }
    friend std::string generateID(const std::string &nume, const std::string &prenume);
    // friend std::ofstream& operator<<(std::ofstream& os, const Client& client);
    friend std::string getTipAbonamentSpecial(const Client &client);
    friend std::ostream &operator<<(std::ostream &, const Client &);
    friend std::istream &operator>>(std::istream &, Client *&);

    
    Client& operator+=(int bilet) {
        this->getPortofel().set_are_bilet(true);
        this->getPortofel().setFonduri(this->portofel.getFonduri() - bilet);
        return *this;
    }

    
};
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
    bool caz_special;
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
    else
    {
        caz_special = false;
    }

    std::cout << "Introduceti suma pe care doriti sa o depuneti in cont:\n";
    int suma=-3;

    while(suma<0)
    {
        is >> suma;
        if(suma<0)
            std::cout<<"Suma nu poate fi negativa. Introduceti o suma valida:\n";
    }
    portofel.setFonduri(suma);

    client = new Client(nume, prenume, pass, id, abonament, portofel, caz_special);

    g << *client;
    g.flush();

    return is;
}
std::ostream &operator<<(std::ostream &stream, const Client &c)
{
    stream << "Nume: " << c.nume << "\n";
    stream << "Prenume: " << c.prenume << "\n";
    stream << "ID: " << c.id << "\n"; 
    stream << "Password: " << c.password << "\n";
    // stream << "Abonament: " << (c.are_abonament ? "Da" : "Nu") << "\n";
    stream << "Caz special: " << (c.caz_special ? "Da" : "Nu") << "\n";
    stream << "Descriere caz special: " << c.caz << "\n";
    stream << "Fonduri disponibile: " << c.portofel.getFonduri() << " RON\n";
    stream << "Bilet: " << (c.portofel.getAreBilet() ? "Da" : "Nu") << "\n";
    stream << "Abonament (portofel): " << (c.portofel.getAreAbonament() ? "Da" : "Nu") << "\n";
    stream << "Tip abonament: " << c.portofel.getTipAbonament() << "\n";
    return stream;
}

void Portofel::afisareFonduri(const Client &client) const
{
    std::cout << "Fonduri disponibile: " << this->fonduri << " RON\n";
    std::cout << "Bilet: " << (this->are_bilet ? "Da" : "Nu") << "\n";
    std::cout << "Abonament: " << (this->are_abonament ? "Da" : "Nu") << "\n";
    std::cout << "Tip abonament: " << this->tip_abonament << "\n";
    std::cout << "Tip abonament special: " << client.getCaz() << "\n";
}

std::string trimTrailing(const std::string &str, const std::string &toRemove)
{
    if (str.size() >= toRemove.size() &&
        str.compare(str.size() - toRemove.size(), toRemove.size(), toRemove) == 0)
    {
        return str.substr(0, str.size() - toRemove.size());
    }
    return str;
}
std::vector<Client *> readClientsFromFile(const std::string &filename)
{
    std::vector<Client *> clients;
    std::ifstream infile(filename);
    if (!infile)
    {
        std::cerr << "Error opening " << filename << std::endl;
        return clients;
    }

    std::string line;
    while (std::getline(infile, line))
    {
        if (line.empty())
            continue;

        std::string nume = line.substr(6);

        std::getline(infile, line);
        std::string prenume = line.substr(9);

        std::getline(infile, line);
        std::string id = line.substr(4);

        std::getline(infile, line);
        std::string password = line.substr(10);

        std::getline(infile, line);
        std::string cazSpecialBoolStr = line.substr(14);
        bool caz_special = (cazSpecialBoolStr == "Da");

        std::getline(infile, line);
        std::string caz = line.substr(23);

        std::getline(infile, line);
        std::string fonduriStr = line.substr(21);
        fonduriStr = trimTrailing(fonduriStr, " RON");
        int fonduri = std::stoi(fonduriStr);

        std::getline(infile, line);
        std::string biletStr = line.substr(7);
        bool are_bilet = (biletStr == "Da");

        std::getline(infile, line);
        std::string abonamentPortofelStr = line.substr(22);
        bool areAbonamentPortofel = (abonamentPortofelStr == "Da");

        std::getline(infile, line);
        std::string tip_abonament = line.substr(15);

        Portofel portofel(fonduri, are_bilet, areAbonamentPortofel, tip_abonament);

        bool areAbonament = false;
        Client *client = new Client(nume, prenume, password, id, areAbonament, portofel, caz_special, caz);
        clients.push_back(client);
    }
    infile.close();
    return clients;
}

std::vector<staff *> readStaffFromFile(const std::string &filename)
{
    std::vector<staff *> staffList;
    std::ifstream infile(filename);
    if (!infile)
    {
        std::cerr << "Error opening " << filename << std::endl;
        return staffList;
    }

    std::string line;
    while (std::getline(infile, line))
    {
        if (line.empty())
            continue;

        std::string nume = line.substr(6);

        std::getline(infile, line);
        std::string prenume = line.substr(9);

        std::getline(infile, line);
        std::string email = line.substr(7);

        std::getline(infile, line);
        std::string password = line.substr(10);

        std::getline(infile, line);
        std::string pozitie = line.substr(9);

        staff *s = new staff(nume, prenume, email, password, pozitie);
        staffList.push_back(s);
    }
    infile.close();
    return staffList;
}
void updateClientsFile(const std::vector<Client *> &clients, const std::string &filename)
{
    std::ofstream outfile(filename, std::ios::trunc); 
    if (!outfile)
    {
        std::cerr << "Error opening " << filename << " for writing." << std::endl;
        return;
    }
    for (const auto &client : clients)
    {
        outfile << *client << "\n";
    }
    outfile.close();
}
void updateStaffFile(const std::vector<staff *> &staffMembers, const std::string &filename)
{
    std::ofstream outfile(filename, std::ios::trunc); 
    if (!outfile)
    {
        std::cerr << "Error opening " << filename << " for writing." << std::endl;
        return;
    }
    for (const auto &s : staffMembers)
    {
        outfile << *s << "\n";
    }
    outfile.close();
}
int main()
{
    const int bilet_metro = 5;
    const int bilet_suprafata = 3;
    const int abonament_metro_luna = 100;
    const int abonament_metro_saptamana = 30;
    const int abonament_metro_zi = 10;
    const int abonament_suprafata = 50;
    const int abonament_special_metro = 10;
    const int abonament_special_suprafata = 5;

    std::regex email_pattern("^[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\\.[a-zA-Z0-9-.]+$");

    mijloc_transport metro("Metro", 5, 10, 30, 100);
    mijloc_transport tramvai("Tramvai", 3, 7, 25, 70);
    mijloc_transport autobuz("Autobuz", 4, 10, 27, 65);

    std::vector<Client *> clienti;
    std::vector<staff *> angajati;

    Client ovidiu("Ovidiu", "Popescu", "1234", "PopescuOvidiu", false, Portofel(120, false, false, "Nu are abonament normal"), false, "Nu se incadreaza in niciun caz special");
    std::cout << ovidiu;
    ovidiu+=bilet_metro;
    std::cout << ovidiu;

    std::cout << "Bun venit la aplicatia de transport!\n";
    staff boss("Andrei", "Paun", "apaun@yahoo.com", "1234", "Manager");
    // std::cout << boss;

    std::vector<Client *> clientVector = readClientsFromFile("clienti.txt");
    std::vector<staff *> staffVector = readStaffFromFile("angajati.txt");
    clientVector.insert(clientVector.end(), clienti.begin(), clienti.end()); // adauga clientii noi la cei cititi din fisier

    bool exit = false;
    while (!exit)
    {
        std::string client_staff;
        std::cout << "Client/Staff?\n";
        while (toLower(client_staff) != "client" && toLower(client_staff) != "Staff")
        {
            std::cout << "Introduceti 'Client' sau 'Staff'\n";
            std::cin >> client_staff;
        }
        if (toLower(client_staff) == "client")
        {
            std::string raspuns;
            std::cout << "Ai cont? (Da/Nu)\n";
            while (toLower(raspuns) != "da" && toLower(raspuns) != "nu")
            {
                std::cout << "Introduceti 'Da' sau 'Nu'\n";
                std::cin >> raspuns;
            }

            if (toLower(raspuns) == "nu")
            {
                Client *client = nullptr;
                std::cin >> client;
                clienti.push_back(client);
                clientVector.push_back(client);
            }
            else if (toLower(raspuns) == "da")
            {
                std::cout << "Sign in\n";
                std::string id, password;
                std::cout << "ID: ";
                std::cin >> id;
                password = getHiddenPassword();
                bool found_cont_client = false;
                for (auto &client : clientVector)
                {
                    if (client->getId() == id && client->getPassword() == password)
                    {
                        found_cont_client = true;
                        std::cout << "Logare reusita!\n";
                        client->afisare();
                        bool logout = false;
                        while (!logout)
                        {
                            std::cout << "Ce doriti sa faceti?\n";
                            std::cout << "1. Depunere bani\n";
                            std::cout << "2. Cumparare bilet\n";
                            std::cout << "3. Afisare date cont\n";
                            std::cout << "4. Logout\n";
                            int optiune;
                            std::cin >> optiune;
                            if (optiune == 1)
                            {
                                std::cout << "Introduceti suma pe care doriti sa o depuneti in cont:\n";
                                int suma;
                                std::cin >> suma;
                                while (suma < 0)
                                {
                                    std::cout << "Suma nu poate fi negativa. Introduceti o suma valida:\n";
                                    std::cin >> suma;
                                }
                                client->depunere(suma);
                                std::cout << "Suma a fost depusa cu succes!\n";
                            }
                            else if (optiune == 2)
                            {
                                std::cout << "Ce tip de bilet doriti sa cumparati?\n";
                                std::cout << "1. Metro\n";
                                std::cout << "2. Tramvai\n";
                                std::cout << "3. Autobuz\n";
                                int raspuns_bilet;
                                std::cin >> raspuns_bilet;
                                if (raspuns_bilet == 1)
                                {
                                    if (client->getFonduri() >= bilet_metro)
                                    {
                                        client->getPortofel().setFonduri(client->getFonduri() - bilet_metro);
                                        client->getPortofel().set_are_bilet(true);
                                        std::cout << "Bilet cumparat cu succes!\n";
                                    }
                                    else
                                    {
                                        std::cout << "Nu aveti suficienti bani in cont pentru a cumpara biletul!\n";
                                    }
                                }
                                else if (raspuns_bilet == 2)
                                {
                                    if (client->getFonduri() >= bilet_suprafata)
                                    {
                                        client->getPortofel().setFonduri(client->getFonduri() - bilet_suprafata);
                                        client->getPortofel().set_are_bilet(true);
                                        std::cout << "Bilet cumparat cu succes!\n";
                                    }
                                }
                            }
                            else if (optiune == 3)
                            {
                                std::cout << *client;
                            }
                            else if (optiune == 4)
                            {
                                logout = true;
                            }
                            else std::cout<<"Optiune invalida!\n";
                        }
                    }
                    
                }
                if (!found_cont_client)
                {
                    std::cout << "Logare nereusita! ID sau parola gresita!\n";
                }
            }
        }
        else if (toLower(client_staff) == "staff")
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
            // Validare email la sign in
            while (!std::regex_match(email, email_pattern))
            {
                std::cout << "Email invalid! Introduceti un email valid:\n";
                std::cin >> email;
            }
            std::cout << "Password: ";
            password = getHiddenPassword();
            bool found = false;
            std::string prenume_nume = prenume + " " + nume;
            if (prenume_nume == "Andrei Paun")
            {
                if (boss.getEmail() == email && boss.getPassword() == password)
                    found = true;
                if (found)
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
                        std::cout << "4. Logout\n";
                        int optiune;
                        std::cin >> optiune;
                        if (optiune == 1)
                        {
                            staff *angajat = nullptr;
                            std::cin >> angajat;
                            angajati.push_back(angajat);
                            staffVector.push_back(angajat);
                            std::cout << "Angajat adaugat cu succes!\n";
                        }
                        else if (optiune == 2)
                        {
                            std::string numeStergere;
                            std::cout << "Introduceti numele angajatului de sters: ";
                            std::cin >> numeStergere;
                            bool found_angajat = false;
                            for (auto it = staffVector.begin(); it != staffVector.end(); ++it)
                            {
                                if ((*it)->getNume() == numeStergere)
                                {
                                    delete *it;
                                    staffVector.erase(it);
                                    std::cout << "Angajat sters!\n";
                                    found_angajat = true;
                                    break;
                                }
                            }
                            if (!found_angajat)
                                std::cout << "Angajatul cu numele " << numeStergere << " nu a fost gasit.\n";
                        }
                        else if (optiune == 3)
                        {
                            std::cout << "Pe cine doriti sa afisati?\n";
                            std::cout << "1. Toti angajatii\n";
                            std::cout << "2. Un angajat\n";
                            int opt_afisare;
                            std::cin >> opt_afisare;
                            if (opt_afisare == 1)
                            {
                                for (auto &angajat : staffVector)
                                    std::cout << *angajat;
                            }
                            else if (opt_afisare == 2)
                            {
                                std::string numeAfisare;
                                std::cout << "Introduceti numele angajatului: ";
                                std::cin >> numeAfisare;
                                bool found_angajat = false;
                                for (auto &angajat : staffVector)
                                {
                                    if (angajat->getNume() == numeAfisare)
                                    {
                                        std::cout << *angajat;
                                        found_angajat = true;
                                        break;
                                    }
                                }
                                if (!found_angajat)
                                    std::cout << "Angajatul cu numele " << numeAfisare << " nu a fost gasit.\n";
                            }
                        }
                        else if (optiune == 4)
                        {
                            logout = true;
                        }
                        else std::cout<<"Optiune invalida!\n";
                        if (logout)
                            std::cout << "Ati iesit din sesiune!\n";
                    }
                }
                else
                {
                    std::cout << "Logare nereusita! Email sau parola gresita!\n";
                }
            }
            else
            {
                bool found_angajat = false;
                for (auto &angajat : staffVector)
                {
                    if (angajat->getEmail() == email && angajat->getPassword() == password)
                        found_angajat = true;
                }
                if (found_angajat)
                {
                    std::cout << "Logare reusita!\n";
                    std::cout << "Ce actiune doriti sa efectuati?\n";
                    std::cout << "1. Incarcare cont cu fonduri\n";
                    std::cout << "2. Schimbare parola cont utilizator\n";
                    int optiune;
                    std::cin >> optiune;
                    if (optiune == 1)
                    {
                        std::string id, pass;
                        std::cout << "Introduceti ID-ul clientului: ";
                        std::cin >> id;
                        std::cout << "Introduceti parola: ";
                        pass = getHiddenPassword();
                        bool found_client = false;
                        for (auto &client : clienti)
                        {
                            if (client->getId() == id && client->getPassword() == pass)
                            {
                                found_client = true;
                                std::cout << "Client gasit!\n";
                                std::cout << "Introduceti suma pe care doriti sa o depuneti in cont: ";
                                int suma;
                                std::cin >> suma;
                                while (suma < 0)
                                {
                                    std::cout << "Suma nu poate fi negativa. Introduceti o suma valida:\n";
                                    std::cin >> suma;
                                }
                                client->depunere(suma);
                                std::cout << "Suma a fost depusa cu succes!\n";
                                client->afisare();
                            }
                        }
                    }
                    else if (optiune == 2)
                    {
                        std::string id;
                        std::cout << "Introduceti ID-ul clientului: ";
                        std::cin >> id;
                        bool found_client = false;
                        for (auto &client : clienti)
                        {
                            if (client->getId() == id)
                            {
                                found_client = true;
                                std::cout << "Client gasit!\n";
                                std::cout << "Introduceti noua parola: ";
                                std::string new_password = getHiddenPassword();
                                client->set_password(new_password);
                                std::cout << "Parola a fost schimbata cu succes!\n";
                                client->afisare();
                            }
                        }
                    }
                    else
                    {
                        std::cout << "Actiune nerecunoscuta!\n";
                    }
                }
                else
                {
                    std::cout << "Logare nereusita! Email sau parola gresita!\n";
                }
            }
            std::cout << "Continuati? (Introduceti 'Da' sau 'Nu')\n";
            std::string continuare;
            int ok_continuare = 0;
            while (!ok_continuare)
            {
                std::cin >> continuare;
                if (toLower(continuare) == "da")
                {
                    ok_continuare = 1;
                    exit = false;
                }
                else if (toLower(continuare) == "nu")
                {
                    ok_continuare = 1;
                    exit = true;
                }
                else
                {
                    std::cout << "Raspuns invalid! Introduceti 'Da' sau 'Nu'\n";
                }
            }
        }

        std::cout << "Doriti sa iesiti din aplicatie? (Da/Nu)\n";
        std::string iesire;
        int ok_citire = 0;
        while (!ok_citire)
        {
            std::cin >> iesire;
            if (toLower(iesire) == "da")
            {
                exit = true;
                ok_citire = 1;
            }
            else if (toLower(iesire) == "nu")
            {
                exit = false;
                ok_citire = 1;
            }
            else
            {
                std::cout << "Raspuns invalid! Introduceti 'Da' sau 'Nu'\n";
            }
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

    updateClientsFile(clientVector, "clienti.txt");
    updateStaffFile(staffVector, "angajati.txt");
    for (auto &client : clientVector)
    {
        delete client;
    }
    for (auto &s : staffVector)
    {
        delete s;
    }

    g.close();
    h.close();
    return 0;
}
