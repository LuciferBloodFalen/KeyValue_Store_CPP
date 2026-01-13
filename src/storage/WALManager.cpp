#include "WALManager.hpp"

#include <fstream>
#include <sstream>
#include <iostream>

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

void WALManager::logDel(const std::string &key)
{
    std::ofstream out(logfile, std::ios::app);
    if (!out.is_open())
        return;

    out << "DEL " << key << "\n";
    out.flush();
    out.close();
}

void WALManager::replay(KeyValueStore &kv)
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

        if (cmd == "SET")
        {
            std::string key;
            ss >> key;

            std::string value;
            std::getline(ss, value);

            while (!value.empty() && value[0] == ' ')
                value.erase(0, 1);

            kv.setInternal(key, value);
        }
        else if (cmd == "DEL")
        {
            std::string key;
            ss >> key;

            kv.delInternal(key);
        }
    }
}

void WALManager::clear()
{
    std::ofstream out(logfile, std::ios::trunc);
    out.close();
}