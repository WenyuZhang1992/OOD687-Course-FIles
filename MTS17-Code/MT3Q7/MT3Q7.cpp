/////////////////////////////////////////////////////////////////////
// MT3Q7.cpp - Execution of Enqueued Callable Objects              //
//                                                                 //
// Jim Fawcett, CSE687 - Midterm Solution, Spring 2017             //
/////////////////////////////////////////////////////////////////////

#include "MT3Q7.h"

int main()
{
  std::cout << "\n  MT3Q7.cpp - Enqueueing and Executing two Callable Objects";
  std::cout << "\n ===========================================================\n";

  using Co = std::function<bool()>;
  using Cb = std::function<void()>;

  Executor<Co, Cb> ex;

  Co q1 = []() { std::cout << "\n  pretending to make query q1"; return true; };
  Cb cb1 = []() { std::cout << "\n  processing results of query q1"; };

  ex.addWorkItem({ q1, cb1 });

  Co q2 = []() { std::cout << "\n  pretending to make query q2"; return true; };
  Cb cb2 = []() { std::cout << "\n  processing results of query q2"; };

  ex.addWorkItem({ q2, cb2 });

  Co q3 = []() { std::cout << "\n  quitting"; return false; };
  ex.addWorkItem({ q3, cb2 });

  ex.wait();
  std::cout << "\n\n";
}