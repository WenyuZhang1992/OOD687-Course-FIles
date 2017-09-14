/////////////////////////////////////////////////////////////////////
// MT3Q4a.cpp - asynchronous invoker using thread                  //
//                                                                 //
// Jim Fawcett, CSE687 - Midterm Solution, Spring 2017             //
/////////////////////////////////////////////////////////////////////
/*
 * This solution can only run global functions and static methods.
*/
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <iostream>
#include <chrono>

template <typename CO>
class Invoker
{
public:
  void invoke(CO& co)
  {
    std::thread t([&]() { 
      co();
    });
    t_ = std::move(t);
  }
  void wait() { t_.join(); }
private:
  std::thread t_;
};

int main()
{
  std::cout << "\n  MT3Q4a - asynchronous invoker using thread";
  std::cout << "\n ============================================\n";

  using namespace std::chrono_literals;
  using CallableType = std::function<void()>;
  CallableType co = []() { 
    std::this_thread::sleep_for(2s);
    std::thread::id id = std::this_thread::get_id();
    std::cout << "\n  running on child thread with id = " << id;
  };

  Invoker<CallableType> invoker;
  invoker.invoke(co);

  // do something useful here
  
  invoker.wait();
  std::cout << "\n  main thread id = " << std::this_thread::get_id() << "\n\n";
}