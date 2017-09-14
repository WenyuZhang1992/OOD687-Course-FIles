/////////////////////////////////////////////////////////////////////
// Inserter.cpp - Variadic inserter for STL Containers             //
//                                                                 //
// Application: CSE687 - Object Oriented Design C++11 demos        //
// Platform:    Dell XPS 2720 Touch, Win 8.1, Visual Studio 2013   //
// Author:      Jim Fawcett, CST 4-187, Syracuse Univesity         //
//              jfawcett@twcny.rr.com                              //
/////////////////////////////////////////////////////////////////////

#include "Inserter.h"
#include "../Helpers/Helpers.h"
#include <string>
#include <vector>
#include <list>
#include <memory>
#include <iostream>

void main()
{
  using Demo = UtilityHelpers::ContainerHelpers;
  using Show = UtilityHelpers::Utilities;
  Show::title("Demonstrate Variadic Templates");
  std::cout << "\n";

  Show::title("Variadic insertion of std::strings");
  std::vector<std::string> vStr;
  inserter(vStr, "one", "two", "three");
  Demo::showItems(vStr);

  Show::title("Variadic insertion of unique_ptr<std::string>s");
  std::vector<std::unique_ptr<std::string>> vPtr;
  using PtrStr = std::unique_ptr < std::string > ;
  using str = std::string;
  inserter(vPtr, PtrStr(new str("one")), PtrStr(new str("two")), PtrStr(new str("three")), PtrStr(new str("four")));

  std::cout << "\n  ";
  for (auto i = begin(vPtr); i != end(vPtr); ++i)
  {
    std::cout << Demo::format<str>() << (*(*i)) << Demo::format<str>();
    if(i != --end(vPtr))
      std::cout << ", ";
  }
  std::cout << "\n\n";
}