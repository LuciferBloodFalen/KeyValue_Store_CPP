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

CommandParser::CommandParser(KeyValueStore &store)
    : kv(store)
{
}

void CommandParser::run()
{
    kv.load();

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

            if (!kv.set(key, value))
            {
                std::cout << "ERROR\n";
            }
            else
            {
                std::cout << "OK\n";
            }
        }
        else if (command == "GET")
        {
            std::string key;
            ss >> key;

            std::cout << kv.get(key) << '\n';
        }
        else if (command == "DEL")
        {
            std::string key;
            ss >> key;

            if (kv.del(key))
            {
                std::cout << "OK\n";
            }
            else
            {
                std::cout << "NULL\n";
            }
        }
        else if (command == "EXIT")
        {
            kv.saveToFile();
            std::cout << "Bye\n";
            break;
        }
        else
        {
            std::cout << "Unknown Command\n";
        }
    }
}