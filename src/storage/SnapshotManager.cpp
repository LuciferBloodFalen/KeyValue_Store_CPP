#include "SnapshotManager.hpp"

#include <fstream>
#include <sstream>

bool SnapshotManager::save() const
{
    std::ofstream out(filepath);
    if (!out.is_open())
        return false;

    for (auto it = kv.begin(); it != kv.end(); ++it)
    {
        out << it->first << "=" << it->second << "\n";
    }

    return true;
}

bool SnapshotManager::load()
{
    std::ifstream in(filepath);
    if (!in.is_open())
        return true;

    kv.clear();

    std::string line;
    while (std::getline(in, line))
    {
        if (line.empty())
            continue;

        auto pos = line.find("=");
        if (pos == std::string::npos)
            continue;

        std::string key = line.substr(0, pos);
        std::string value = line.substr(pos + 1);

        if (!key.empty())
            kv.set(key, value);
    }

    return true;
}