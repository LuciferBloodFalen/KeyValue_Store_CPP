#pragma once

#include <string>

#include "KeyValueStore.hpp"

class SnapshotManager
{
private:
    std::string filepath;
    KeyValueStore& kv;

public:
    bool save() const;
    bool load();
};