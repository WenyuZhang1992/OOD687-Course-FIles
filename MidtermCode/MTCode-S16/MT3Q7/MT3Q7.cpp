///////////////////////////////////////////////////////////////////////
// MT3Q7.cpp - Recursive thread creation                             //
//                                                                   //
// Jim Fawcett, CSE687 - Object Oriented Design, Midterm Spring 2016 //
///////////////////////////////////////////////////////////////////////

#include <thread>
#include <chrono>
#include <iostream>
#include <string>
#include <functional>
#include <conio.h>
#include "../Utilities/Utilities.h"
/*
 *  The purpose of this odd processing is to start a set of
 *  threads in a guaranteed order, perhaps to do some setup.
 *
 *  Suppose, for example, you are writting a card game with
 *  each player running on a thread to be able to react to
 *  game play in real time, but it is important to start in
 *  a specific order (clockwise around the table).
 *
 *  Note: you were not expected to provide a template function.
 *  I did that just to illustrate the points above.
 */
template <typename CallObj>
void threadProc(size_t count, CallObj co)
{
  std::cout << "\n  entered threadProc with count = " << count;
  
  // Do setup for this thread, probably different from 
  // child thread's setup
  co(count);
  std::this_thread::sleep_for(std::chrono::milliseconds(100));

  if (count++ < 10)
  {
    std::thread t(threadProc<CallObj>, count, co);
    t.detach();
  }
  // Do this thread's work here, perhaps in a long-running
  // loop while descendents concurrently do their own work.

  std::cout << "\n  leaving threadProc with count = " << --count;
}

using namespace Utilities;
using Utils = StringHelper;
using Co = std::function<void(size_t)>;

void main()
{
  Utils::Title("MT3Q7 - Recursive thread creation");

  Co f = [](size_t count)
  {
    std::cout << "\n  doing setup for thread #" << count;
  };

  std::thread t(threadProc<Co>, 1, f);
  t.detach();

  std::cout << "\n  press any key to exit: \n";
  _getche();
  std::cout << "\n\n";
}