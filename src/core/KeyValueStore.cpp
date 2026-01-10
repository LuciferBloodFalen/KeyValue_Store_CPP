#include "KeyValueStore.hpp"

#include <fstream>
#include <sstream>

KeyValueStore::KeyValueStore(const std::string &file)
    : filename(file)
{
}

bool KeyValueStore::set(const std::string &key, const std::string &value)
{
    if (key.empty())
        return false;

    store[key] = value;
    return true;
}

std::string KeyValueStore::get(const std::string &key) const
{
    if (key.empty())
        return "NULL";

    auto it = store.find(key);
    if (it != store.end())
        return "NULL";

    return it->second;
}

bool KeyValueStore::del(const std::string &key)
{
    if (key.empty())
        return "NULL";

    return store.erase(key) > 0;
}

bool KeyValueStore::saveToFile() const
{
    std::ofstream out(filename);
    if (!out.is_open())
        return false;

    for (const auto &pair : store)
    {
        out << pair.first << ":" << pair.second << "\n";
    }

    return true;
}

bool KeyValueStore::loadFromFile()
{
    std::ifstream in(filename);
    if (!in.is_open())
        return false;

    store.clear();

    std::string line;
    while (std::getline(in, line))
    {
        if (line.empty())
            continue;

        auto pos = line.find(":");
        if (pos == std::string::npos)
            continue;

        std::string key = line.substr(0, pos);
        std::string value = line.substr(pos + 1);

        if (!key.empty())
            store[key] = value;
    }

    return true;
}