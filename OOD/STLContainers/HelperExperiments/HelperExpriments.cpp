/////////////////////////////////////////////////////////////////////
// HelperExperimentss.cpp - Utilities for STL container demos      //
//                                                                 //
// Application: CSE687 - Object Oriented Design C++11 demos        //
// Platform:    Dell XPS 2720 Touch, Win 8.1, Visual Studio 2013   //
// Author:      Jim Fawcett, CST 4-187, Syracuse Univesity         //
//              jfawcett@twcny.rr.com                              //
/////////////////////////////////////////////////////////////////////

#include "HelperExperiments.h"

std::string UtilityHelpers::showEnumType(ShowType showType)
{
  switch (showType)
  {
  case ShowType::range_for:       return "range_for";
  case ShowType::foreach_functor: return "foreach_functor";
  case ShowType::foreach_lambda:  return "foreach_lambda";
  default: throw(std::exception("unknown enumeration"));
  }
}

#ifdef TEST_HELPERS

using namespace UtilityHelpers;

int main()
{
  using Test = TestContainers;  // type alias

  TestContainers::title("Demonstrating Helpers Package", '=');

  TestContainers::title("demo std::vector<int>");
  std::vector<int> v{ 0, 1, 2, 3, 4, 3, 2 };
  Test::show(v, ShowType::range_for);

  TestContainers::title("demo std::list<std::string>");
  std::list<std::string> l{ "zero", "one", "two", "three", "four", "three", "two" };
  Test::show(l, ShowType::foreach_functor);

  TestContainers::title("demo std::string");
  std::string s{ "a test string" };
  Test::show(s, ShowType::foreach_lambda);

  TestContainers::title("demo std::map<int, std::string>");
  std::map<int, std::string> m{ { 1, "one" }, { 2, "two" }, { 3, "three" }, { 4, "four" }, { 5, "five" } };
  Test::showKeyValues(m);

  TestContainers::title("demo std::unordered_map<int, std::string>");
  std::unordered_map<std::string, int> u{ { "one", 1 }, { "two", 2 }, { "three", 3 }, { "four", 4 }, { "five", 5 } };
  Test::showKeyValuesWithIterator(u);

  std::cout << "\n\n";
}

#endif
