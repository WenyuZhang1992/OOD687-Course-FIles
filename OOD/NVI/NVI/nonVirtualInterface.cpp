/////////////////////////////////////////////////////////////////////
// nonVirtualInterface.cpp - demonstrate NVI pattern               //
//                                                                 //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2005       //
/////////////////////////////////////////////////////////////////////

#include "nonVirtualInterface.h"

void main()
{
  std::cout << "\n  Demonstrating the Non-Virtual Interface Pattern"
            << "\n =================================================\n";

  nonVirtInterf base;
  nonVirtInterf* p1 = &base;
  p1->doSomeThing();
  std::cout << "\n";

  derivedNVI derived; 
  nonVirtInterf* p2 = &derived;
  p2->doSomeThing();
  std::cout << "\n\n";
}
