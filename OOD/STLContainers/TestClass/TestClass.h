#ifndef TESTCLASS_H
#define TESTCLASS_H
/////////////////////////////////////////////////////////////////////////////
// TestClass.h - Implemented to Support testing operations on classes      //
//                                                                         //
// Application:  CSE687 - OOD demonstration, Spring 2014                   //
// Platform:     Dell XPS 2720 Touch, Win 8.1 Pro, Visual Studio 2012      //
// Author:       Jim Fawcett, Syracuse University, CST 4-187               //
//               jfawcett@twcny.rr.com, http://ecs.syr.edu/faculty/fawcett //
/////////////////////////////////////////////////////////////////////////////
/*
*  Package Operations
* --------------------
*  This package provides a single class: TestClass.  It is intended to support
*  testing of containers and your custome classes.
*  - TestClass provides all the standard class methods
*  - all its methods enunciate.  That is, they write to the console as they
*    execute.
*
*  Required Files:
* -----------------
* - TestClass.h, TestClass.cpp, Helpers.h, Helpers.cpp
*
*  Build Command:
* ----------------
*    devenv STLContainers.sln /rebuild debug
*
*  Maintenance History:
* ----------------------
*  Ver 1.0 : 8 Jan 14
*  - first release
*/

#include <string>

class Test
{
public:
  Test();                           // void constructor, sometimes called default constructor
  Test(const std::string& name);    // constructor for named instance
  Test(const Test& t);              // copy constructor
  Test(Test&& t);                   // move constructor
  Test& operator=(const Test& t);   // copy assignment operator
  Test& operator=(Test&& t);        // move assignment operator
  virtual ~Test();                  // destructor
  std::string& name();
  void say();
private:
  std::string name_;
};
#endif
