#include "KeyValueStore.hpp"
cw
bool KeyValueStore::set(const std::string &key, const std::string &value)
{
    if (key.empty())
        return false;

    store[key] = value;
    return true;
}

std::string KeyValueStore::get(const std::string &key) const
{
    if (key.empty())
        return "";

    auto it = store.find(key);
    if (it == store.end())
        return "";

    return it->second;
}

bool KeyValueStore::del(const std::string &key)
{
    if (key.empty())
        return false;

    return store.erase(key) > 0;
}

bool KeyValueStore::exists(const std::string &key) const
{
    return store.find(key) != store.end();
}

size_t KeyValueStore::size() const
{
    return store.size();
}

std::unordered_map<std::string, std::string>::const_iterator KeyValueStore::begin() const
{
    return store.begin();
}

std::unordered_map<std::string, std::string>::const_iterator KeyValueStore::end() const
{
    return store.end();
}

void KeyValueStore::clear()
{
    store.clear();
}