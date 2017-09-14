///////////////////////////////////////////////////////////////////////
// MT2Q4.cpp - Run function asynchronously                           //
//                                                                   //
// Jim Fawcett, CSE687 - Object Oriented Design, Midterm Spring 2016 //
///////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <thread>
#include <functional>
#include "../Utilities/Utilities.h"

template <typename CallObj>
std::thread asynchRun(CallObj co)
{
  std::thread t(co);
  return t;
}

void hello()
{
  std::cout << "\n\n  hello function:";
  for (size_t i = 0; i < 5; ++i)
    std::cout << "\n    running on thread with id = " << std::this_thread::get_id();
}

using namespace Utilities;
using Utils = StringHelper;

void main()
{
  Utils::Title("MT2Q4 - Running function asychronously");

  std::cout << "\n  main thread id = " << std::this_thread::get_id();

  std::function<void()> f = 
  []()
  {
    std::cout << "\n\n  lambda:";
    for (size_t i = 0; i < 5; ++i)
      std::cout << "\n    running on thread with id = " << std::this_thread::get_id();
  };
  std::thread t = asynchRun(hello);
  t.join();
  t = asynchRun(f);
  t.join();
  std::cout << "\n\n";
}
