/////////////////////////////////////////////////////////////////////
// Vectors.cpp - Utilities for STL container demos                 //
//                                                                 //
// Application: CSE687 - Object Oriented Design C++11 demos        //
// Platform:    Dell XPS 2720 Touch, Win 8.1, Visual Studio 2013   //
// Author:      Jim Fawcett, CST 4-187, Syracuse Univesity         //
//              jfawcett@twcny.rr.com                              //
/////////////////////////////////////////////////////////////////////
/*
 *  std::vector<T> is an expandable, indexable array of T elements
 */

#include <vector>
#include <string>
#include <iostream>
#include "../Helpers/Helpers.h"

using namespace UtilityHelpers;

int main()
{
  using Test = ContainerHelpers;  // type alias

  try
  {
    Utilities::title("Demonstrating Vectors Package", '=');

    // std::vector<T> can be initialized with a list of T items

    Utilities::title("demo std::list<int>");
    std::vector<int> vecInt{ 0, 1, 2, 3, 4, 3, 2 };
    Test::showItems(vecInt);

    // std::vector<T> can be indexed

    std::cout << "\n  The fourth element of vector is: " << vecInt[5] << "\n";

    // you can add and remove elements from the end with push_back(T t) and pop_back();

    std::cout << "\n  pushing back the element -3:\n";
    vecInt.push_back(-3);
    Test::showItems(vecInt);

    // insert elements with an iterator pointing to the element which will follow

    std::cout << "\n  inserting -3 at beginning:\n";
    vecInt.insert(begin(vecInt), -3);
    Test::showItems(vecInt);

    // you can insert a list of elements with an iterator pointing to the following element

    std::cout << "\n  inserting list of three values after second item:\n";
    vecInt.insert(begin(vecInt) + 2, { -1, -2, -3 });
    Test::showItems(vecInt);

    // any type with correct copy and/or move semantics can be stored in a std::vector

    Utilities::title("demo std::vector<std::string>");
    std::vector<std::string> vecStr{ "zero", "one", "two", "three", "four", "three", "two" };
    Test::showItems(vecStr);
  }
  catch (std::exception ex)
  {
    std::cout << "\n\n" << ex.what();
  }
  std::cout << "\n\n";
}

