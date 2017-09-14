/////////////////////////////////////////////////////////////////////
// ManagedClasses.cpp - Demonstrates use of managed C++ classes    //
//                                                                 //
// Jim Fawcett, CSE775 - Distributed Objects, Spring 2003          //
/////////////////////////////////////////////////////////////////////
// Built with Empty Managed C++ Project wizard                     //
/////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include "ManagedClasses.h"

using namespace std;

//----< display a message on console >-------------------------------

void msg(const std::string& s)
{
  cout << "\n  " << s;
  std::string underline(s.size()+2,'-');
  cout << "\n " << underline << endl;
}
//
int main()
{
///////////////////////////////////////////////////////////////
// managed class holding a StringBuilder reference
//  - changes to the value held also change the
//    reference used for construction

  msg("managed class holding reference to a StringBuilder object");

  StringBuilder^ rStr = gcnew StringBuilder("Hello World");
  Console::Write("\n  {0}\n",rStr);

  Managed^ rManaged = gcnew Managed(rStr);
  Console::Write("\n  {0}\n",rManaged->value());

  //  This does not work nor does casting help
  //  rManaged->value() = gcnew StringBuilder("A New World");

  rManaged->value()->Remove(0,rManaged->value()->Length);  // have to remove
  rManaged->value()->Append("A Replaced World");           // then replace
  Console::Write("\n  {0}\n",rManaged->value());           // expected change
  Console::Write("\n  {0}\n",rStr);                        // changed too!
  
///////////////////////////////////////////////////////////////
// managed class holding a StringBuilder pointer
//  - changes to the value referred to, but not
//    the pointer used for construction

  msg("managed class holding pointer to a StringBuilder object");

  StringBuilder% NewStr = *gcnew StringBuilder("A New World");
  Console::Write("\n  {0}\n",%NewStr);

  Managed% New = *gcnew Managed(%NewStr);
  Console::Write("\n  {0}\n",New.value());

  //  can't assign to this reference
  //  New.value() = gcnew StringBuilder("A Newer World");
  
  New.value(gcnew StringBuilder("A Newer World"));
  Console::Write("\n  {0}\n",New.value());
  Console::Write("\n  {0}\n",%NewStr);

  NewManaged^ newMan = gcnew NewManaged();
  newMan->str->Append(%NewStr);
  Console::Write("\n  {0}\n",newMan->str);

  msg("managed classes derive from object: here is pNew->ToString()");

  Console::Write("\n  {0}\n",New.ToString());

  NewerManaged^ newerMan = gcnew NewerManaged();
  newerMan->value().Append("A string written to StringBuilder%");
  Console::Write("\n  {0}\n\n", newerMan->value().ToString());
}