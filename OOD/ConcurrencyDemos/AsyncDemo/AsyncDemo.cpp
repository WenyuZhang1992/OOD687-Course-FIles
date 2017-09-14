///////////////////////////////////////////////////////////////////////////
// AsyncDemo.cpp - demonstrate thread, async, future, mutex, lock_guard  //
//                                                                       //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2017             //
///////////////////////////////////////////////////////////////////////////
/*
 * Demonstrate:
 * - std::this_thread - provides access to running thread
 * - async            - template function that runs a callable object on child thread
 * - future<T>        - member function get() blocks until thread has terminated with result
 * - mutex            - lock with member functions lock() and unlock()
 * - lock_guard<L>    - constructor aquires lock L, destructor releases lock
 *
 *  Async runs a function asynchronously, making it easy to pass arguments to the function
 *  and retrieve its return value, even though the function runs on a child thread.
 */
#include <thread>
#include <future>
#include <mutex>
#include <chrono>
#include <iostream>

using namespace std::chrono_literals;

//----< demo function displays msg with interleaved spaces >---------

size_t speak(const std::string& msg)
{
  /* 
    all callers share the same lock, mtx - that is essential! 
  */
  static std::mutex mtx;
  /* 
    std::lock_guard acquires mutex lock on construction
    and releases when it goes out of scope 
  */
  std::lock_guard<std::mutex> lgrd(mtx);  // comment to get race condition

  std::cout << "\n  running on thread: " << std::this_thread::get_id() << "\n  ";

  for (char ch : msg)
  {
    std::cout << ch << ' ';
    std::this_thread::sleep_for(50ms);
  }
  std::cout << "\n";
  return msg.size();
}
//----< Demonstrate asynchronous processing >------------------------
/*
 * The async template function and future template class make it easy
 * to run functions that take inputs and return a value asynchronously.
*/
int main()
{
  std::cout << "\n  Demonstrating async and future";
  std::cout << "\n ================================\n";

  std::cout << "\n  main thread id = " << std::this_thread::get_id() << "\n";

  std::string msg = "hello world";

  std::future<size_t> result = std::async(std::launch::async, speak, msg);

  std::this_thread::sleep_for(1ms);
  speak(msg);

  std::cout << "\n  message length result = " << result.get() << "\n\n";
}