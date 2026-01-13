#pragma once

#include <string>

#include "KeyValueStore.hpp"

class WALManager
{
private:
    std::string logfile;

public:
    explicit WALManager(std::string &filename);

    void logSet(const std::string &key, const std::string &value);
    void logdel(const std::string &key);

    void replay(KeyValueStore &ks);
    void clear();
};