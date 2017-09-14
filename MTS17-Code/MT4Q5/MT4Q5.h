#pragma once
/////////////////////////////////////////////////////////////////////
// MT4Q5.h - ThreadSafeMap                                         //
//                                                                 //
// Jim Fawcett, CSE687 - Midterm Solution, Spring 2017             //
/////////////////////////////////////////////////////////////////////

#include <unordered_map>
#include <string>
#include <vector>
#include <thread>
#include <mutex>


class ThreadSafeMap
{
public:
  using Key = std::string;
  using Value = std::vector<Key>;
  using Map = std::unordered_map<Key, Value>;
  using iterator = Map::iterator;

  bool hasKey(const Key& key);
  bool insert(const Key& key, const Value& value);
  Value find(const Key& key);
  bool set(const Key& key, const Value& value);
  bool remove(const Key& key);
  void clear();
  iterator begin();
  iterator end();
  std::recursive_mutex& getLock() { return mtx_;  }
private:
  Map map_;
  std::recursive_mutex mtx_;
};

inline bool ThreadSafeMap::hasKey(const Key& key)
{
  std::lock_guard<std::recursive_mutex> lck(mtx_);
  if (map_.find(key) != map_.end())
    return true;
  return false;
}

inline bool ThreadSafeMap::insert(const Key& key, const Value& value)
{
  std::lock_guard<std::recursive_mutex> lck(mtx_);
  if (hasKey(key))
    return false;
  map_[key] = value;
  return true;
}

inline ThreadSafeMap::Value ThreadSafeMap::find(const Key& key)
{
  std::lock_guard<std::recursive_mutex> lck(mtx_);
  if (map_.find(key) == map_.end())
  {
    Value retVal;  // empty collection
    return retVal;
  }
  return map_[key];
}

inline bool ThreadSafeMap::set(const Key& key, const Value& value)
{
  std::lock_guard<std::recursive_mutex> lck(mtx_);
  if (map_.find(key) == map_.end())
    return false;
  map_[key] = value;
  return true;
}

inline bool ThreadSafeMap::remove(const Key& key)
{
  std::lock_guard<std::recursive_mutex> lck(mtx_);
  if (map_.find(key) == map_.end())
    return false;
  map_.erase(key);
  return true;
}

inline void ThreadSafeMap::clear()
{
  std::lock_guard<std::recursive_mutex> lck(mtx_);
  map_.clear();
}

inline ThreadSafeMap::iterator ThreadSafeMap::begin()
{
  std::lock_guard<std::recursive_mutex> lck(mtx_);
  return map_.begin();
}

inline ThreadSafeMap::iterator ThreadSafeMap::end()
{
  std::lock_guard<std::recursive_mutex> lck(mtx_);
  return map_.end();
}

