///////////////////////////////////////////////////////////////////////
// MT3Q4b.cpp - asynchronous invoker using thread, returning result  //
//                                                                   //
// Jim Fawcett, CSE687 - Midterm Solution, Spring 2017               //
///////////////////////////////////////////////////////////////////////

#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <iostream>
#include <chrono>

///////////////////////////////////////////////////////////////////////
// ThreadSafeResult class
// - similar to blocking queue, but only holds one result
// - this is similar to using Promise and Future
//
template <typename R>
class ThreadSafeResult
{
public:
  void setResult(R r) 
  { 
    std::cout << "\n  setting result in ThreadSafeResult::setResult";
    {
      std::lock_guard<std::mutex> lck(mtx_);
      result_ = r;
      set = true;
    }
    cv_.notify_one();
  }
  R getResult()
  {
    std::unique_lock<std::mutex> lck(mtx_);
    std::cout << "\n  returning result in ThreadSafeResult::getResult";
    if (set)
      return result_;
    while (!set)
    {
      cv_.wait(lck);
    }
    return result_;
  }
private:
  std::mutex mtx_;
  std::condition_variable cv_;
  R result_;
  bool set = false;
};

template <typename CO, typename R>
class Invoker
{
public:
  void invoke(CO& co)
  {
    std::thread t([&]() { 
      std::cout << "\n  reading result in child thread, ";
      R result = co();
      std::cout << "\n  in child thread, result is " << result << std::endl;
      result_.setResult(result); 
    });
    t_ = std::move(t);
  }
  R getResult() { return result_.getResult(); }
  void wait() { t_.join(); }
private:
  ThreadSafeResult<R> result_;
  std::thread t_;
};

int main()
{
  std::cout << "\n  MT1Q3b - asynchronous invoker using thread";
  std::cout << "\n ============================================\n";

  using namespace std::chrono_literals;
  using CallableType = std::function<size_t()>;
  CallableType co = []() { 
    std::this_thread::sleep_for(2s);
    std::thread::id id = std::this_thread::get_id();
    std::cout << "\n  child thread id = " << id;
    return 42;
  };

  Invoker<CallableType, size_t> invoker;
  invoker.invoke(co);
  std::cout << "\n  result = " << invoker.getResult();
  std::cout << "\n  main thread id = " << std::this_thread::get_id() << "\n\n";
  invoker.wait();
}