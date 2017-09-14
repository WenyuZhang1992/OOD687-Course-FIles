/////////////////////////////////////////////////////////////////////
// Lists.cpp - Utilities for STL container demos                   //
//                                                                 //
// Application: CSE687 - Object Oriented Design C++11 demos        //
// Platform:    Dell XPS 2720 Touch, Win 8.1, Visual Studio 2013   //
// Author:      Jim Fawcett, CST 4-187, Syracuse Univesity         //
//              jfawcett@twcny.rr.com                              //
/////////////////////////////////////////////////////////////////////
/*
 *  std::list<T> is based on a doubly-linked list and is not indexable
 */

#include "../Helpers/Helpers.h"

using namespace UtilityHelpers;

int main()
{
  using Test = ContainerHelpers;  // type alias

  try
  {
    Utilities::title("Demonstrating Lists Package", '=');

    // std::list<T> can be initialized with a list of T items

    Utilities::title("demo std::list<double>");
    std::list<double> listDbl{ 0.5, 1.5, 2.5, 3.5, 4.5, 3.5, 2.5 };
    Test::showItems(listDbl);

    // You can't index list so you have to walk the list to get to a specific item.
    // Here we're walking with an iterator.

    std::list<double>::iterator iter = begin(listDbl);
    for (size_t i = 0; i < 2; ++i)
    {
      ++iter;
    }
    std::cout << "\n  The third element of list is: " << *iter;

    // Alternately we can blow away items until we get what we want.
    // Here we're destructively walking a copy.

    std::list<double> temp = listDbl;  
    for (size_t i = 0; i < 3; ++i)
      temp.pop_front();
    std::cout << "\n  The fourth element of list is: " << temp.front() << "\n";

    // Items are added and removed with push_back(T t) and pop_back().

    double item = -3.0;
    std::cout << "\n  pushing back the element " << item << ":\n";
    listDbl.push_back(item);
    Test::showItems(listDbl);
    
    // We can add or remove items anywhere in the list with insert and erase, including at the beginning.

    std::cout << "\n  inserting " << item + 1 << " at beginning:\n";
    listDbl.insert(begin(listDbl), item + 1);
    Test::showItems(listDbl);

    // At the beginning it would be slightly easier to use push_front(T t) or pop_front().

    std::cout << "\n  inserting " << item << " at beginning:\n";
    listDbl.push_front(item);
    Test::showItems(listDbl);

    std::cout << "\n  removing second item:\n";
    listDbl.erase(++begin(listDbl));
    Test::showItems(listDbl);

    // We can add a list of items before the item pointed to by an iterator.

    std::cout << "\n  inserting list of three values after second item:\n";
    listDbl.insert(++(++begin(listDbl)), { -1.0, -2.1, -3.2 });
    Test::showItems(listDbl);

    // std::list can hold any instances of types with copy and/or move semantics.

    Utilities::title("demo std::list<std::string>");
    std::list<std::string> listStr{ "zero", "one", "two", "three", "four", "three", "two" };
    Test::showItems(listStr);
  }
  catch (std::exception ex)
  {
    std::cout << "\n\n" << ex.what();
  }
  std::cout << "\n\n";
}
