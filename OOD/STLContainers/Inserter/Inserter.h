#ifndef INSERTER_H
#define INSERTER_H
/////////////////////////////////////////////////////////////////////
// Inserter.h - Variadic inserter for STL Containers               //
//                                                                 //
// Application: CSE687 - Object Oriented Design C++11 demos        //
// Platform:    Dell XPS 2720 Touch, Win 8.1, Visual Studio 2013   //
// Author:      Jim Fawcett, CST 4-187, Syracuse Univesity         //
//              jfawcett@twcny.rr.com                              //
/////////////////////////////////////////////////////////////////////
/*
*  Package Operations
* --------------------
*  This package provides two variadic template functions:
*  - void inserter<C,T>(C& c, const T& t, ...)
*    where T is a copyable type
*  - void inserter<C,T>(C& c, T&& t, ...)
*    where T is a moveable type
*
*  Required Files:
* -----------------
* - Inserter.h, Inserter.cpp, Helpers.h, Helpers.cpp
*
*  Build Command:
* ----------------
*    devenv STLContainers.sln /rebuild debug
*
*  Maintenance History:
* ----------------------
*  Ver 1.0 : 9 Jan 14
*  - first release
*/
#include <string>
#include <sstream>

/////////////////////////////////////////////////////////////////////
// variadic template function to push_back copyable objects
// - this really isn't very useful since container initialization 
//   works for copyable objects

template <typename C, typename T>
void inserter(C& c, const T& t)
{
  c.push_back(t);
}

template < typename C, typename T, typename... Args >
void inserter(C& c, const T& t, Args... args)
{
  c.push_back(t);
  inserter(c, args...);
}

/////////////////////////////////////////////////////////////////////
// variadic template function to push_back movable objects
// - this can be used to initialize a container with moveable
//    but not copyable objects
// - it's useful because initialization_lists don't work with
//   moveable objects

template <typename C, typename T>
void inserter(C& c, T&& t)
{
  c.push_back(std::move(t));
}

template < typename C, typename T, typename... Args >
void inserter(C& c, T&& t, Args&&... args)
{
  c.push_back(std::move(t));
  inserter(c, args...);
}

#endif
