#include "SnapshotManager.hpp"

#include <fstream>
#include <sstream>

bool SnapshotManager::save() const
{
    std::ofstream out(filepath);
    if (!out.is_open())
        return false;

    // Iterate the unordered_map store in Class KeyValueStore that is being referenced as private kv in this class
        // for (const auto &pair : kv)
    // for (const auto *it = kv.begin(); it!=kv.end())
    // {
    //     out << pair.first << "=" << pair.second << "\n";
    // }

    return true;
}

bool SnapshotManager::load()
{
    /*
    std::ifstream in(filename);
//     if (!in.is_open())
//         return false;

//     store.clear();

//     std::string line;
//     while (std::getline(in, line))
//     {
//         if (line.empty())
//             continue;

//         auto pos = line.find(":");
//         if (pos == std::string::npos)
//             continue;

//         std::string key = line.substr(0, pos);
//         std::string value = line.substr(pos + 1);

//         if (!key.empty())
//             store[key] = value;
//     }

//     return true;
*/
}