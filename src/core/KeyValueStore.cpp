#include "KeyValueStore.hpp"

KeyValueStore::KeyValueStore(WALManager &wal)
    : wal(wal) {}

void KeyValueStore::set(const std::string &key, const std::string &value)
{
    wal.logSet(key, value);
    store[key] = value;
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

void KeyValueStore::del(const std::string &key)
{
    wal.logDel(key);
    store.erase(key);
}

void KeyValueStore::setInternal(const std::string &key, const std::string &value)
{
    store[key] = value;
}

void KeyValueStore::delInternal(const std::string &key)
{
    store.erase(key);
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