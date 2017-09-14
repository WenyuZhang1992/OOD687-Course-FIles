/////////////////////////////////////////////////////////////////////////////
// TestClass.cpp - Implemented to Support testing operations on classes    //
//                                                                         //
// Application:  CSE687 - OOD demonstration, Spring 2014                   //
// Platform:     Dell XPS 2720 Touch, Win 8.1 Pro, Visual Studio 2012      //
// Author:       Jim Fawcett, Syracuse University, CST 4-187               //
//               jfawcett@twcny.rr.com, http://ecs.syr.edu/faculty/fawcett //
/////////////////////////////////////////////////////////////////////////////

#include "TestClass.h"
#include "..\Helpers\Helpers.h"
#include <iostream>
#include <string>
#include <vector>
#include <memory>

//----< default constructor >----------------------------------------------

Test::Test()
{
  std::cout << "\n  void construction of Test";
  name_ = "Test";
}
//----< promotion constructor >--------------------------------------------

Test::Test(const std::string& name)
{
  name_ = name;
  std::cout << "\n  named construction of " << name_;
}
//----< reset instance name string >---------------------------------------

std::string rename(const std::string& prefix, const std::string& sourceName)
{
  if (prefix != sourceName.substr(0, 4))
    return prefix + " of " + sourceName;
  else
    return sourceName;
}
//----< copy constructor >-------------------------------------------------

Test::Test(const Test& t) : name_(t.name_) 
{
  std::cout << "\n  copy of " << name_;
  name_ = rename("copy", t.name_);
}
//----< move constructor >-------------------------------------------------

Test::Test(Test&& t) : name_(t.name_)
{
  std::cout << "\n  move of " << name_;
  name_ = rename("move", t.name_);
  t.name_ = "been moved";
}
//----< copy assignment operator >-----------------------------------------

Test& Test::operator=(const Test& t)
{
  std::cout << "\n  copy assignment of " << name_;
  if (this != &t)
  {
    name_ = rename("copy", t.name_);
  }
  return *this;
}
//----< move assignment operator >-----------------------------------------

Test& Test::operator=(Test&& t)
{
  std::cout << "\n  move assignment of " << name_;
  if (this != &t)
  {
    name_ = rename("move", t.name_);
    t.name_ = "been moved";
  }
  return *this;
}
//----< destructor >-------------------------------------------------------

Test::~Test()
{
  std::cout << "\n  destruction of " << name_;
}
//----< name "property" >--------------------------------------------------

std::string& Test::name()
{
  return name_;
}
//----< enunciator >-------------------------------------------------------

void Test::say()
{
  std::cout << "\n  my name is " << name_;
}
//----< cosmetic object that emits line feeds on termination >-------------

struct lineFeeds
{
  ~lineFeeds()
  {
    std::cout << "\n\n";
  }
} cosmetic;
//----< demonstration of move construction >-------------------------------

Test demoFunc()
{
  Test demo;
  demo.name() = "function demo";
  return demo;
}
//----< test stub >--------------------------------------------------------

#include <stdexcept>

int main()
{
  using Helper = UtilityHelpers::Utilities;
  Helper::title("Demonstrate Test Class");
  Test t("Fred");         // named construction
  Test t1 = t;            // copy construction
  Test t2 = demoFunc();   // move construction
  Test t3;
  t3 = t1;                // copy assignment
  t3 = Test();            // move assignment from temporary
  std::cout << "\n";

  t1.name() = "t1";
  t2.name() = "t2";
  t3.name() = "t3";

  Helper::title("Creating initialized std::vector of Tests");
  std::vector<Test> vt{ t1, t2, std::move(t3) };
  for (auto& e : vt)
  {
    e.say();
  }
  std::cout << "\n";

  Helper::title("Testing push_backs");
  Test t4("t4");
  Test t5("t5");
  vt.push_back(t4);
  vt.push_back(std::move(t5));
  for (auto& e : vt)
  {
    e.say();
  }
  std::cout << "\n";

  Helper::title("Creating vector of smart pointers");
  /*
   *  - unique_ptr<T> is a smart pointer to an instance t of type T
   *  - it assumes it is the only reference to t and that t is stored on the native heap
   *  - since it represents unique ownership, it cannot be copied or assigned, only moved
   *  - when it goes out of scope, either through a normal exit from the scope where it was defined
   *    or because an exception was thrown, it calls delete on its iternal pointer to t
   */
  std::unique_ptr<Test> sp1(new Test("t6"));
  std::unique_ptr<Test> sp2(new Test("t7"));
  std::vector<std::unique_ptr<Test>> vp;
  vp.push_back(std::move(sp1));
  vp.push_back(std::move(sp2));
  /////////////////////////////////////////////////////////////////////////
  // surprisingly this doesn't work.  Initializer_lists are constant so
  // you can copy but can't move out of them.  Unique_ptr is moveable but
  // not copyable so you have to use push_back
  //
  //  std::vector<std::unique_ptr<Test>> vp { std::move(sp1), std::move(sp2) };
  //

  sp2.reset(new Test("t8"));  // re-initializes sp2 to point to t8, original object was moved into vector so nothing to delete
  sp2.reset(new Test("t9"));  // re-initializes sp2 to point to t9 then deletes t8

  for (auto& p : vp)
  {
    p->say();
  }
  std::cout << "\n";

  Helper::title("Done with testing");
}
