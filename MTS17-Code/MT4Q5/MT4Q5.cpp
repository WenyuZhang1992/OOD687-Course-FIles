/////////////////////////////////////////////////////////////////////
// MT4Q5.cpp - ThreadSafeMap                                       //
//                                                                 //
// Jim Fawcett, CSE687 - Midterm Solution, Spring 2017             //
/////////////////////////////////////////////////////////////////////

#include "MT4Q5.h"
#include <iostream>
#include <thread>
#include <atomic>
#include <sstream>

void show(ThreadSafeMap& map)
{
  ThreadSafeMap::iterator iter;
  std::recursive_mutex& mtx = map.getLock();
  std::lock_guard<std::recursive_mutex> lck(mtx);

  for (auto item : map)
  {
    std::cout << "\n  " << item.first << " : ";
    for (auto val : item.second)
      std::cout << val << " ";
  }
  std::cout << "\n";
}

std::string toString(int i)
{
  std::ostringstream out;
  out << i;
  return out.str();
}
void test(ThreadSafeMap& tsm)
{
  static std::atomic<int> i = 0;
  for (size_t j = 0; j < 5; ++j)
  {
    ++i;
    ThreadSafeMap::Value val;
    val.push_back(std::string("file") += toString(i.load()));
    ++i;
    val.push_back(std::string("file") += toString(i.load()));
    ++i;
    std::string key = std::string("file") += toString(i.load());
    tsm.insert(key, val);
    {
      std::recursive_mutex& mtx = tsm.getLock();
      std::lock_guard<std::recursive_mutex> lck(mtx);
      std::cout << "\n  inserting \"" << key << " in tsm on thread " << std::this_thread::get_id();
    }
  }
}
int main()
{
  std::cout << "\n  MT4Q5 - ThreadSafeMap";
  std::cout << "\n =======================";

  ThreadSafeMap tsmap;

  ThreadSafeMap::Value val1;
  val1.push_back("first_value");
  val1.push_back("second_value");
  tsmap.insert("test1", val1);

  ThreadSafeMap::Value val2;
  val2.push_back("third_value");
  val2.push_back("fourth_value");
  tsmap.insert("test2", val2);

  show(tsmap);

  std::cout << "\n  starting thread tests";
  std::cout << "\n -----------------------";
  std::thread t1(test, std::ref(tsmap));
  std::thread t2(test, std::ref(tsmap));
  t1.join();
  t2.join();
  std::cout << "\n";
  show(tsmap);

  std::cout << "\n\n";
}