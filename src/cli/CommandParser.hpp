#pragma once

#include <string>

#include "KeyValueStore.hpp"
#include "SnapshotManager.hpp"
#include "WALManager.hpp"

class CommandParser
{
private:
    KeyValueStore &kv;
    SnapshotManager &snapshot;
    WALManager &wal;

    void handleSet(const std::string &key, const std::string &value);
    void handleGet(const std::string &key);
    void handleDel(const std::string &key);

    static std::string toUpper(const std::string &s);

public:
    CommandParser(KeyValueStore &kv, SnapshotManager &snapshot, WALManager &wal);

    void run();
};