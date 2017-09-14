///////////////////////////////////////////////////////////////////////////
// AsyncMemberFunction.cpp - running member function asynchronously      //
//                                                                       //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2017             //
///////////////////////////////////////////////////////////////////////////
/*
* Demonstrate:
* - std::this_thread - provides access to running thread
* - async            - template function that runs a callable object on child thread
* - future<T>        - member function get() blocks until thread has terminated with result
*
*  Async can run a non-static member function asynchronously, making it easy to pass 
*  arguments to the method and retrieve its return value, even though the function runs 
*  on a child thread.
*/

#include <thread>
#include <future>
#include <string>
#include <iostream>
#include <chrono>

class X
{
public:

  X(const std::string& msg = "class X") : msg_(msg) {}
  size_t longSay()
  {
    size_t count = 10;
    std::cout << "\n  ";
    for (size_t i = 0; i < count; ++i)
    {
      using namespace std::chrono_literals;
      std::cout << "\n  class X ";
      std::this_thread::sleep_for(3s);
    }
    return count;
  }
private:
  std::string msg_;
};

int main()
{
  using namespace std::chrono_literals;

  /*--- Note use of member function declaration and instance of class ---*/

  X x;
  std::future<size_t> fut = std::async(std::launch::async, &X::longSay, &x);

  std::cout << "\n  ";
  while (fut.wait_for(2s) != std::future_status::ready)
    std::cout << "waiting ... ";
  std::cout << "\n  waited for " << fut.get() << " iterations\n\n";
}