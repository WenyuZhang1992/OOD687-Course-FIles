///////////////////////////////////////////////////////////////////////
// MT1Q6.cpp - Passing Arguments to Threads                          //
//                                                                   //
// Jim Fawcett, CSE687 - Object Oriented Design, Midterm Spring 2016 //
///////////////////////////////////////////////////////////////////////

#include <thread>
#include <iostream>
#include <string>
#include "../Utilities/Utilities.h"

void hello(const std::string& one, const std::string& two)
{
  std::cout << "\n  arguments passed to hello are: " << one.c_str();
  std::cout << " and " << two.c_str();
}

class MyFunctor
{
public:
  MyFunctor(const std::string& one, const std::string& two)
    : _one(one), _two(two) {}
  void operator()() 
  {
    std::cout << "\n  arguments passed to MyFunctor are: " << _one.c_str();
    std::cout << " and " << _two.c_str();
  }
private:
  std::string _one;
  std::string _two;
};

using namespace Utilities;
using Utils = StringHelper;

int main()
{
  Utils::Title("MT1Q6 - Three ways to pass arguments to threads");

  std::thread t1(hello, "one", "two");               // explicitly passed to thread constructor
  t1.join();
  std::thread t2(MyFunctor("one", "two"));           // passed as member data of functor
  t2.join();
  std::string one = "one";
  std::string two = "two";
  std::thread t3(                                    // passed as lambda captured data
    [=]() {
      std::cout << "\n  arguments passed to lambda are: " << one.c_str();
      std::cout << " and " << two.c_str();
    }
  );
  t3.join();
  std::cout << "\n\n";
}