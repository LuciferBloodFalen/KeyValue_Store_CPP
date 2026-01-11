#pragma once

#include <string>
#include <unordered_map>

class KeyValueStore
{
private:
    std::unordered_map<std::string, std::string> store;
    // std::string filename;

public:
    // explicit KeyValueStore(const std::string &file);

    bool set(const std::string &key, const std::string &value);
    std::string get(const std::string &key) const;
    bool del(const std::string &key);
    bool exists(const std::string &key) const;
    size_t size() const;

    // bool saveToFile() const;
    // bool loadFromFile();
};