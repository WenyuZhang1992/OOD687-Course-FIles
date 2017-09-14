/////////////////////////////////////////////////////////////////////
// MT1Q3.cpp - namespace usings table                              //
//                                                                 //
// Jim Fawcett, CSE687 - Midterm Solution, Spring 2017             //
/////////////////////////////////////////////////////////////////////


#include "MT1Q3.h"
#include <iostream>

using namespace CodeAnalysis;

//----< does map have file key? >------------------------------------

bool Usings::hasFile(File file)
{
  if (uMap.find(file) != uMap.end())
  {
    return true;
  }
  return false;
}
//----< add a namespace for specified file >-------------------------

void Usings::insert(File file, Namespace nmspace)
{
  if (hasFile(file))
  {
    uMap[file].push_back(nmspace);
    return;
  }
  Using uses;
  uses.push_back(nmspace);
  uMap[file] = uses;
}
//----< return set of usings for specified file >--------------------

Usings::Using Usings::usings(File file)
{
  if (hasFile(file))
    return uMap[file];
  return Using();
}
//----< clear all entries in map >-----------------------------------

void Usings::clear()
{
  uMap.clear();
}

#pragma warning (disable : 4101)  // unused variable warning

namespace Example
{
  class X {};
}

int main()
{
  std::cout << "\n  Demonstrating MT1Q3 - Namespace Table";
  std::cout << "\n =======================================\n";

  Example::X x;

  Usings u;
  Usings::File f = "MT1Q3.cpp";
  u.insert(f, "Example");
  u.insert(f, "CodeAnalysis");

  std::cout << "\n  file \"" << f << "\" uses namespaces:";
  for (Usings::Namespace n : u.usings(f))
  {
    std::cout << "\n    " << n;
  }
  std::cout << "\n\n";
}