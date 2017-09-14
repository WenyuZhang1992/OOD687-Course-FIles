#pragma once
/////////////////////////////////////////////////////////////////////
// MT1Q3.h - namespace usings table                                //
//                                                                 //
// Jim Fawcett, CSE687 - Midterm Solution, Spring 2017             //
/////////////////////////////////////////////////////////////////////

#include <unordered_map>
#include <string>
#include <vector>

namespace CodeAnalysis
{
  class Usings
  {
  public:
    using File = std::string;
    using Namespace = std::string;
    using Using = std::vector<Namespace>;

    bool hasFile(File file);
    void insert(File file, Namespace nmspace);
    Using usings(File file);
    void clear();
  private:
    std::unordered_map<File, Using> uMap;
  };
}

