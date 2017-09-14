/////////////////////////////////////////////////////////////////////
// MT2Q7b.cpp - Asynchronous Call with Callback                    //
//                                                                 //
// Jim Fawcett, CSE687 - Midterm Solution, Spring 2017             //
/////////////////////////////////////////////////////////////////////
/*
 * This answer has a lot more than required, but is included here to
 * show that the original question can grow into something interesting.
 *
 * This invoker enqueues Callable Objects and Callback Objects
 * for execution on a child thread.
 *
 * The NoSqlDb, from Project #1, could use this approach to make
 * thread-safe queries by concurrent users.  The Callable Object
 * represents a query, and the callback represents the processing
 * we need on the query results.
 */

#include "../Cpp11-BlockingQueue/Cpp11-BlockingQueue.h"
#include <thread>
#include <functional>
#include <string>

/////////////////////////////////////////////////////////////////////
// Invoker class
// - AsyncInvoke enqueues WorkItems on an input queue.
//   Each WorkItem contains a Callable Object and Callback Object.
// - A child thread is created in the Invoker constructor to first
//   execute the Callable Object, then execute the CallBack Object.
// - Since only the child thread is executing calls, the invocations
//   are thread-safe.
// - Invoker uses a thread-safe blocking queue, so multiple concurrent
//   callers can safely enqueue WorkItems.
//
template <typename CO, typename CB>
class Invoker
{
public:
  using WorkItem = struct { CO co; CB cb; };

  Invoker();
  void asyncInvoke(CO co, CB cb);  // asynchronous invocation
  void wait() 
  { 
    if (t_.joinable())
      t_.join();
  }
private:
  Async::BlockingQueue<WorkItem> queue_;
  std::thread t_;
};
//----< construct Invoker, starting the dequeueing thread >----------

template<typename CO, typename CB>
Invoker<CO, CB>::Invoker()
{
  // start up a private dequeueing thread

  std::thread t(
    [&]() { 
      while (true) {
        WorkItem wi = queue_.deQ();
        if (!wi.co(wi.cb))
        {
          std::cout << "\n  thread shutting down";
          return;
        }
      }
    }
  );
  t_ = std::move(t);  // this is necessary so we can wait on the child thread
}
//----< asynchronous execution of Callable and Callback >------------
/*
* This assumes that Callable is designed to invoke the callback
* when it's processing completes.
*/
template<typename CO, typename CB>
void Invoker<CO, CB>::asyncInvoke(CO co, CB cb)
{
  WorkItem wi{ co, cb };
  queue_.enQ(wi);
}

#include <sstream>

std::string toString(size_t i)
{
  std::ostringstream out;
  out << i;
  return out.str();
}

int main()
{
  std::cout << "\n  MT2Q7b - Asynchronous Invoker with Callback";
  std::cout << "\n =============================================";

  using CallBackType = std::function<void()>;
  using CallType = std::function<bool(CallBackType)>;
  using Message = std::string;

  Invoker<CallType, CallBackType> invoker;

  // example Callback

  CallBackType cb = []() { std::cout << "\n  this is a callback"; };
  
  for (size_t i = 0; i < 5; ++i)
  {
    // example Callable Object

    Message msg = "Message #" + toString(i);
    CallType ct = [msg](CallBackType cb) { std::cout << "\n  " << msg; cb(); return true; };
    invoker.asyncInvoke(ct, cb);
  }
  // make termination WorkItem

  CallBackType null = []() {};
  Message msg = "quit";
  CallType end = [msg](CallBackType cb) { return false; };
  invoker.asyncInvoke(end, null);
  invoker.wait();
  std::cout << "\n\n";
}