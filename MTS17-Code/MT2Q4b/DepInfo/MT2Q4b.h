#pragma once
/////////////////////////////////////////////////////////////////////
// MT2Q4b.h - Package Dependency class using NoSqlDb               //
//                                                                 //
// Jim Fawcett, CSE687 - Midterm Solution, Spring 2017             //
/////////////////////////////////////////////////////////////////////

#include "../NoSqlDb/NoSqlDb.h"
#include <string>
#include <vector>

class PkgDep
{
public:
  using File = std::string;
  using Dependencies = std::vector<File>;
  using Descrip = std::string;

  PkgDep& insert(const File& depending, const File& dependedOn);
  Dependencies retrieve(const File& depending);
  void show();
private:
  NoSQLDB::NoSqlDb<Descrip> db_;
};