#pragma once

#include <string>

#include "KeyValueStore.hpp"

class SnapshotManager
{
private:
    std::string filepath;
    KeyValueStore &kv;

    size_t writeCount;
    size_t snapshotThreshold;

public:
    explicit SnapshotManager(const std::string &path,  KeyValueStore &kv, size_t threshold = 1000);
    void onWrite();
    bool shouldSnapshot() const;

    bool save();
    bool load();
};