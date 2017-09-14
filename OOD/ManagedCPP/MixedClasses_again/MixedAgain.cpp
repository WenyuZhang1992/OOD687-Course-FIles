/////////////////////////////////////////////////////////////////////
// MixedAgain.cpp - Demonstrates use of managed and unmanaged      //
//                  C++ classes holding references to each other   //
//                                                                 //
// Jim Fawcett, CSE775 - Distributed Objects, Spring 2003          //
/////////////////////////////////////////////////////////////////////
// Built with Empty Managed C++ Project wizard                     //
/////////////////////////////////////////////////////////////////////

using namespace System;
using namespace System::Text;

#include <iostream>
#include <string>
#include "MixedAgain.h"

using namespace std;

void N1::say()
{ 
  std::cout << "\n  Hello from instance of native C++ class"; 
}

R1::R1() : pN(new N1) {}

R1::~R1() { delete pN; }

void R1::say()
{
  Console::Write("\n  Hello from instance of managed reference class");
  std::cout << "\n  calling method on pointer to native type I hold:";
  pN->say();
}

N2::N2() : rR(gcnew R2) {}

N2::~N2() { delete rR; }

void N2::say()
{ 
  std::cout << "\n  Hello from instance of native C++ class"; 
  std::cout << "\n  calling method on managed reference type I hold:";
  rR->say();
}

void R2::say()
{
  Console::Write("\n  Hello from instance of managed reference class");
}
//----< demo mixing native C++ and managed C++ classes >-------------

void main()
{
  std::cout << "\n  Demo Mixed classes holding references to each other";
  std::cout << "\n =====================================================\n";
  std::cout.flush();

  R1 r1;
  r1.say();
  std::cout << "\n";

  N2 n2;
  n2.say();

  std::cout << "\n\n";
}