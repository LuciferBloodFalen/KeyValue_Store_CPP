#include "CommandParser.hpp"

#include <iostream>
#include <sstream>
#include <string>

std::string CommandParser::toUpper(const std::string &s)
{
    std::string result = s;
    for (char &c : result)
    {
        c = std::toupper(c);
    }
    return s;
}

CommandParser::CommandParser(KeyValueStore &kv, SnapshotManager &snapshot, WALManager &wal)
    : kv(kv), snapshot(snapshot), wal(wal)
{
}

void CommandParser::run()
{

    std::string line;
    std::cout << "KeyValueStore started. Type EXIT to quit.\n";

    while (true)
    {
        std::cout << "kv> ";
        if (!std::getline(std::cin, line))
        {
            break;
        }

        std::stringstream ss(line);
        std::string command;
        ss >> command;

        if (command.empty())
        {
            continue;
        }

        command = toUpper(command);

        if (command == "SET")
        {
            std::string key, value;
            ss >> key;
            std::getline(ss, value);

            while (!value.empty() && value[0] == ' ')
            {
                value.erase(0, 1);
            }

            if (key.empty() || value.empty())
            {
                std::cout << "Usage: SET key value\n";
                continue;
            }

            handleSet(key, value);
        }
        else if (command == "GET")
        {
            std::string key;
            ss >> key;

            if (key.empty())
            {
                std::cout << "Usage: GET key\n";
                continue;
            }

            handleGet(key);
        }
        else if (command == "DEL")
        {
            std::string key;
            ss >> key;

            if (key.empty())
            {
                std::cout << "Usage: DEL key\n";
                continue;
            }

            handleDel(key);
        }
        else if (command == "EXIT")
        {
            snapshot.save();
            wal.clear();
            std::cout << "Bye\n";
            break;
        }
        else if (!command.empty())
        {
            std::cout << "Unknown Command\n";
        }
    }
}

void CommandParser::handleSet(const std::string &key, const std::string &value)
{
    wal.logSet(key, value);
    kv.setInternal(key, value);
    snapshot.onWrite();

    if(snapshot.shouldSnapshot())
    {
        snapshot.save();
        wal.clear();
    }
}

void CommandParser::handleGet(const std::string &key)
{
    std::string value = kv.get(key);
    if (!value.empty())
        std::cout << value << "\n";
    else
        std::cout << "(nil)\n";
}

void CommandParser::handleDel(const std::string &key)
{
    wal.logDel(key);
    kv.delInternal(key);
    snapshot.onWrite();

    if(snapshot.shouldSnapshot())
    {
        snapshot.save();
        wal.clear();
    }
}