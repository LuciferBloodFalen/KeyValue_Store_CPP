#include "KeyValueStore.hpp"

bool KeyValueStore::set(const std::string& key, const std::string& value)
{
    if(key.empty())
        return false;

    store[key] = value;
    return true;
}

std::string KeyValueStore::get(const std::string& key) const
{
    if(key.empty())
        return "NULL";
    
    auto it = store.find(key);
    if(it != store.end())
        return "NULL";

    return it->second;
}

bool KeyValueStore::del(const std::string& key)
{
    if(key.empty())
        return "NULL";

    return store.erase(key) > 0;
}