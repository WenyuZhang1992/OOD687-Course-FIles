/////////////////////////////////////////////////////////////////////
// MT3Q4.cpp - Asynchronous Execution                              //
//                                                                 //
// Jim Fawcett, CSE687 - Midterm Solution, Spring 2017             //
/////////////////////////////////////////////////////////////////////

#include <thread>
#include <future>
#include <iostream>
#include <chrono>

//----< global function >--------------------------------------------

size_t theOriginalMeaningOfLife()
{
  using namespace std::chrono_literals;
  std::this_thread::sleep_for(5s);
  return 42;
}

class A
{
public:
  //----< non-static member function >---------------------

  size_t theMeaningOfLife()
  {
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(10s);
    return meaning;
  }
  //----< static member function >-------------------------

  static size_t anotherMeaningOfLife()
  {
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(15s);
    return 84;
  }
private:
  size_t meaning = 42;
};

//----< wait for future to arrive >----------------------------------

void waiting(std::future<size_t>& fut)
{
  using namespace std::chrono_literals;

  std::cout << "  ";
  while (fut.wait_for(3s) != std::future_status::ready)
    std::cout << "waiting ... ";
  std::cout << "\n  the answer is " << fut.get() << "\n";
}
//----< back to the future >-----------------------------------------
/*
 * Runs global functions and static methods asynchronously
*/
template <typename CO, typename R>
class Invoker
{
public:
  std::future<R> invoke(CO co);
};

template <typename CO, typename R>
std::future<R> Invoker<CO, R>::invoke(CO co)
{
  return std::async(std::launch::async, co);
}
/*
* Runs non-static methods asynchronously
*/
template <typename CO, typename I, typename R>
class MF_Invoker
{
public:
  std::future<R> invoke(CO co, I* pI);
};

template<typename CO, typename I, typename R>
std::future<R> MF_Invoker<CO, I, R>::invoke(CO co, I* pI)
{
  return std::async(std::launch::async, co, pI);
}

int main()
{
  std::cout << "\n  MT3Q4 - The Meaning of Life - Thanks Douglas Adams";
  std::cout << "\n ====================================================\n";
  A a;
  using MemPtr = size_t(A::*)();
  MF_Invoker<MemPtr, A, size_t> mf_invoker;
  std::future<size_t> futMF = mf_invoker.invoke(&A::theMeaningOfLife, &a);
  std::cout << "\n  the meaning of life is:\n";
  waiting(futMF);

  using FP = size_t(*)();
  using GlobPtr = size_t(*)();
  Invoker<GlobPtr, size_t> invoker;
  std::future<size_t> futGF = invoker.invoke(&theOriginalMeaningOfLife);
  std::cout << "\n  the original meaning of life is:\n";
  waiting(futGF);

  using FP = size_t(*)();
  std::future<size_t> futSMF = invoker.invoke(&A::anotherMeaningOfLife);
  std::cout << "\n  another meaning of life is:\n";
  waiting(futSMF);
  std::cout << "\n\n";
}