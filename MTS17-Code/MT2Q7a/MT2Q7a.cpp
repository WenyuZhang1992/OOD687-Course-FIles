/////////////////////////////////////////////////////////////////////
// MT2Q7a.cpp - Synchronous Invocation with Callback               //
//                                                                 //
// Jim Fawcett, CSE687 - Midterm Solution, Spring 2017             //
/////////////////////////////////////////////////////////////////////

#include <functional>
#include <string>

template <typename CO, typename CB>
class Invoker
{
public:
  void invoke(CO co, CB cb);
};

template<typename CO, typename CB>
void Invoker<CO, CB>::invoke(CO co, CB cb)
{
  co(cb);
}

#include <sstream>
#include <iostream>

std::string toString(size_t i)
{
  std::ostringstream out;
  out << i;
  return out.str();
}

int main()
{
  std::cout << "\n  MT2Q7a - Synchronous Invoker with Callback";
  std::cout << "\n ============================================";

  using CallBackType = std::function<void()>;
  using CallType = std::function<void(CallBackType)>;
  using Message = std::string;

  Invoker<CallType, CallBackType> invoker;

  CallBackType cb = []() { std::cout << "\n  this is a callback"; };
  
  for (size_t i = 0; i < 5; ++i)
  {
    Message msg = "Message #" + toString(i);
    CallType ct = [=](CallBackType cb) { std::cout << "\n  " << msg; cb(); };
    invoker.invoke(ct, cb);
  }
  std::cout << "\n\n";
}