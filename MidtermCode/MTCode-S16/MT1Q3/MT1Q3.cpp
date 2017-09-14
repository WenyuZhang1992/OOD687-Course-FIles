///////////////////////////////////////////////////////////////////////
// MT1Q3.cpp - Executing Callable Objects                            //
//                                                                   //
// Jim Fawcett, CSE687 - Object Oriented Design, Midterm Spring 2016 //
///////////////////////////////////////////////////////////////////////


#include <iostream>
#include "../Utilities/Utilities.h"

// function accepting and executing any callable object

template <class CallObj>
void Executor(CallObj& co)
{
  co();      // invocation of callable object
}
// example callable object

void hello()
{
  std::cout << "\n  Hello from hello()";
}
// example callable object

class MyFunctor
{
public:
  MyFunctor(const std::string& msg) : _msg(msg) {}

  void operator()()
  {
    std::cout << "\n  " << _msg.c_str() << " from MyFunctor";
  }
private:
  std::string _msg;
};

using namespace Utilities;
using Utils = StringHelper;

int main()
{
  Utils::Title("MT1Q3 - Executing Callable Objects");

  Executor(hello);
  MyFunctor mf("Hi");
  Executor(mf);

  // example callable object

  std::string msg = "Hi again";
  Executor(
    [=]() { std::cout << "\n  " << msg.c_str() << " from lambda"; }
  );

  std::cout << "\n\n";

}