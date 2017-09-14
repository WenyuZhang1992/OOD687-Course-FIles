/////////////////////////////////////////////////////////////////////
// Helpers.cpp - Utilities for STL container demos                 //
//                                                                 //
// Application: CSE687 - Object Oriented Design C++11 demos        //
// Platform:    Dell XPS 2720 Touch, Win 8.1, Visual Studio 2013   //
// Author:      Jim Fawcett, CST 4-187, Syracuse Univesity         //
//              jfawcett@twcny.rr.com                              //
/////////////////////////////////////////////////////////////////////

#include "Helpers.h"

#ifdef TEST_HELPERS

using namespace UtilityHelpers;

int main()
{
  using Test = ContainerHelpers;  // type alias

  Utilities::title("Demonstrating Helpers Package", '=');

  Utilities::title("demo std::vector<int>");
  std::vector<int> v { 0, 1, 2, 3, 4, 3, 2 };
  Test::showItems(v);

  Utilities::title("demo std::list<std::string>");
  std::list<std::string> l{ "zero", "one", "two", "three", "four", "three", "two" };
  Test::showItems(l);

  Utilities::title("demo std::string");
  std::string s{ "a test string" };
  Test::showItems(s);

  Utilities::title("demo std::map<int, std::string>");
  std::map<int, std::string> m{ { 1, "one" }, { 2, "two" }, { 3, "three" }, { 4, "four" }, { 5, "five" } };
  Test::showPairs(m);

  Utilities::title("demo std::unordered_map<int, std::string>");
  std::unordered_map<std::string, int> u{ { "one", 1 }, { "two", 2 }, { "three", 3 }, { "four", 4 }, { "five", 5 } };
  Test::showPairs(u);

  std::cout << "\n\n";
}

#endif
