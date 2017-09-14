///////////////////////////////////////////////////////////////////////
// MT5Q5.cpp - Lambda                                                //
//                                                                   //
// Jim Fawcett, CSE687 - Object Oriented Design, Midterm Spring 2016 //
///////////////////////////////////////////////////////////////////////

#include <iostream>
#include "../Utilities/Utilities.h"

using namespace Utilities;
using Utils = StringHelper;

int main()
{
  Utils::Title("MT5Q5 - addition lambda");
  putline();

  int x = 5;
  int z = 6;

  std::cout << "\n  lambda captures x value = " << x;
  std::cout << ", adds to input y value = " << z;
  std::cout << " and returns "  << [x](int y) { return x + y;} (z);

  std::cout << "\n\n";
}