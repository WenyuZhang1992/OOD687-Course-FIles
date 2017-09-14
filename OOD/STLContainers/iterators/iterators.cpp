/////////////////////////////////////////////////////////////////////
// iterators.cpp - STL container iterators demo                    //
//                                                                 //
// Application: CSE687 - Object Oriented Design C++11 demos        //
// Platform:    Dell XPS 2720 Touch, Win 8.1, Visual Studio 2013   //
// Author:      Jim Fawcett, CST 4-187, Syracuse Univesity         //
//              jfawcett@twcny.rr.com                              //
/////////////////////////////////////////////////////////////////////
/*
 *  iterators are smart pointers designed to navigate through a specific
 *  STL container.  They have most of the interface of native pointers.
 */
#include "../Helpers/Helpers.h"
#include <vector>
#include <list>
#include <string>
#include <iostream>

template <typename T>
struct AddOne : std::unary_function<T, T>
{
  void operator()(T& t) { t += 1; }
};

int main()
{
  using Test = UtilityHelpers::ContainerHelpers;
  using Show = UtilityHelpers::Utilities;

  Show::title("Demonstrating STL Iterators", '=');

  Show::title("Starting collection is a std::vector<int>");
  std::vector<int> vint{ 1, 2, 3, 4, 3, 2, 1, 0, -1 };
  Test::showItems(vint);

  std::vector<int>::iterator iter = std::find(begin(vint), end(vint), 3);
  std::cout << "\n  value found = " << *iter << "\n";

  Show::title("Using for_each to add 1 to each element of collection");
  for_each(begin(vint), end(vint), AddOne<int>());
  Test::showItems(vint);

  Show::title("Using explicit iterator loop to subtract 1 from each element of collection");
  for (auto iter = begin(vint); iter != end(vint); ++iter)
  {
    *iter -= 1;
  }
  Test::showItems(vint);

  std::vector<int>::iterator viter = begin(vint);
  std::cout << "\n  1st  element is \"" << (*viter) << "\"";
  std::cout << "\n  2nd  element is \"" << *(++viter) << "\"";
  std::cout << "\n  3rd  element is \"" << *(++viter) << "\"";
  std::cout << "\n  last element is \"" << *(--end(vint)) << "\"\n";

  Show::title("New collection is std::list<std::string>");
  std::list<std::string> lstr{ "one", "two", "three", "four" };
  Test::showItems(lstr);

  std::list<std::string>::iterator liter = begin(lstr);
  std::cout << "\n  1st  element is \"" << *liter << "\"";
  std::cout << "\n  2nd  element is \"" << *(++liter) << "\"";
  std::cout << "\n  3rd  element is \"" << *(++liter) << "\"";
  std::cout << "\n  last element is \"" << *(--end(lstr)) << "\"";
  std::cout << "\n\n";
}
