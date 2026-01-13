#pragma once

#include <string>
#include <unordered_map>

#include "WALManager.hpp"

class KeyValueStore
{
private:
    std::unordered_map<std::string, std::string> store;
    WALManager &wal;

public:
    explicit KeyValueStore(WALManager &wal);

    void set(const std::string &key, const std::string &value);
    std::string get(const std::string &key) const;
    void del(const std::string &key);

    void setInternal(const std::string &key, const std::string &value);
    void delInternal(const std::string &key);

    bool exists(const std::string &key) const;
    size_t size() const;
    void clear();

    std::unordered_map<std::string, std::string>::const_iterator begin() const;
    std::unordered_map<std::string, std::string>::const_iterator end() const;
};