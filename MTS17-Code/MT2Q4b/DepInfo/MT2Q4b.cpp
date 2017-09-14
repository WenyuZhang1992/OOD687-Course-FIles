/////////////////////////////////////////////////////////////////////
// MT2Q4b.cpp - Package Dependency class using NoSqlDb             //
//                                                                 //
// Jim Fawcett, CSE687 - Midterm Solution, Spring 2017             //
/////////////////////////////////////////////////////////////////////

#include "MT2Q4b.h"

using namespace NoSQLDB;

PkgDep& PkgDep::insert(const File& depending, const File& dependedOn)
{
  Element<Descrip> depElement;
  if (!db_.hasKey(depending))
  {
    depElement.name = depending;
    Dependencies deps;
    deps.push_back(dependedOn);
    depElement.children = deps;
    db_.saveRecord(depending, depElement);
  }
  else
  {
    depElement = db_.value(depending);
    Dependencies deps = depElement.children;
    deps.push_back(dependedOn);
    depElement.children = deps;
    db_.saveValue(depending, depElement);
  }
  return *this;
}

PkgDep::Dependencies PkgDep::retrieve(const File& depending)
{
  if (db_.hasKey(depending))
  {
    return Dependencies(db_.value(depending).children);
  }
  Dependencies empty;
  return empty;
}

void PkgDep::show()
{
  for (auto item : db_)
  {
    std::cout << "\n  " << item.first << " : ";
    for (auto file : Dependencies(db_.value(item.first).children))
      std::cout << file << " ";
  }
  std::cout << "\n";
}

int main()
{
  PkgDep pd;
  pd.insert("file1", "fileA").insert("file1", "fileB");
  pd.insert("file2", "fileC").insert("file2", "fileD").insert("file2", "fileE");
  pd.show();

  std::cout << "\n  file1 depends on: ";
  for (auto file : pd.retrieve("file1"))
  {
    std::cout << " " << file;
  }
  std::cout << "\n\n";
}