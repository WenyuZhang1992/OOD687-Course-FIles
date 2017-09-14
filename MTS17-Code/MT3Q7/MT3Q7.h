#pragma once
/////////////////////////////////////////////////////////////////////
// MT3Q7.h - Execution of Enqueued Callable Objects                //
//                                                                 //
// Jim Fawcett, CSE687 - Midterm Solution, Spring 2017             //
/////////////////////////////////////////////////////////////////////

#include <functional>
#include <thread>
#include "../Cpp11-BlockingQueue/Cpp11-BlockingQueue.h"

template<typename CO, typename CB>
class Executor
{
public:
  using WorkItem = struct { CO co; CB cb; };

  Executor();
  void addWorkItem(WorkItem wi);
  void wait();
private:
  std::thread executeThread_;
  Async::BlockingQueue<WorkItem> queue_;
};

template<typename CO, typename CB>
Executor<CO, CB>::Executor()
{
  std::thread t(
    [&]() {
      while (true)
      {
        WorkItem wi = queue_.deQ();
        if(!wi.co())
          break;
        wi.cb();
      }
    }
  );
  executeThread_ = std::move(t);
}

template<typename CO, typename CB>
void Executor<CO, CB>::addWorkItem(WorkItem wi)
{
  queue_.enQ(wi);
}

template<typename CO, typename CB>
void Executor<CO, CB>::wait()
{
  executeThread_.join();
}