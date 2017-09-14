/////////////////////////////////////////////////////////////////////
// MT4Q7.cpp - display Run-time TypeId                             //
//                                                                 //
// Jim Fawcett, CSE687 - Midterm Solution, Spring 2017             //
/////////////////////////////////////////////////////////////////////

#include <string>
#include <iostream>

template<typename T>
std::string typeOf(const T& t)
{
  return typeid(t).name();
}

int main()
{
  class Widget {};

  std::cout << "\n  typeOf(\"a string\") returns \"" << typeOf("a string") << "\"";
  std::cout << "\n  typeOf(std::string(\"another string\")) returns \"" << typeOf(std::string("another string")) << "\"";
  std::cout << "\n  typeOf(Widget) returns \"" << typeOf(Widget()) << "\"";
  std::cout << "\n\n";
}