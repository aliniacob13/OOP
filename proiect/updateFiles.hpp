#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "Client.hpp"
#include "Staff.hpp"
class Client;
class staff;

class FileHelper{
    public:
        static void updateClientsFile(const std::vector<Client*>& clients, const std::string& filename);
        static void updateStaffFile(const std::vector<staff*>& staffMembers, const std::string& filename);
};

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

