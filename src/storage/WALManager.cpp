#include "WALManager.hpp"

#include <fstream>
#include <sstream>

WALManager::WALManager(std::string &filename)
    : logfile(filename)
{
}

void WALManager::logSet(const std::string &key, const std::string &value)
{
    std::ofstream out(logfile, std::ios::app);
    if (!out.is_open())
        return;

    out << "SET " << key << " " << value << "\n";
    out.flush();
    out.close();
}

void WALManager::logdel(const std::string &key)
{
    std::ofstream out(logfile, std::ios::app);
    if (!out.is_open())
        return;

    out << "DEL " << key << "\n";
    out.flush();
    out.close();
}

void WALManager::replay(KeyValueStore &ks)
{
    std::ifstream in(logfile);
    if (!in.is_open())
        return;

    std::string line;
    while (std::getline(in, line))
    {
        std::stringstream ss(line);
        std::string cmd;
        ss >> cmd;

        if(cmd == "SET")
        {
            std::string key;
            ss >> key;

            std::string value;
            std::getline(ss, value);
        }
        else if(cmd == "DEL")
        {
            // 
        }
    }
    
}

void WALManager::clear()
{
    //
}