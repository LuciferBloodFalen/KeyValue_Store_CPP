#pragma once

#include <string>

#include "KeyValueStore.hpp"

class CommandParser
{
private:
    KeyValueStore &kv;

    static std::string toUpper(const std::string &s);

public:
    explicit CommandParser(KeyValueStore &store);

    void run();
};