#include "SnapshotManager.hpp"

#include <fstream>
#include <sstream>

SnapshotManager::SnapshotManager(const std::string &path, KeyValueStore &kv, size_t threshold)
    : filepath(path), kv(kv), snapshotThreshold(threshold) {}

void SnapshotManager::onWrite()
{
    ++writeCount;
}

bool SnapshotManager::shouldSnapshot() const
{
    return writeCount >= snapshotThreshold;
}

bool SnapshotManager::save()
{
    std::ofstream out(filepath);
    if (!out.is_open())
        return false;

    for (auto it = kv.begin(); it != kv.end(); ++it)
    {
        out << it->first << "=" << it->second << "\n";
    }

    writeCount = 0;
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