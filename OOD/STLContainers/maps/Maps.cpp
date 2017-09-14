/////////////////////////////////////////////////////////////////////
// Maps.cpp - demo std::map container                              //
//                                                                 //
// Application: CSE687 - Object Oriented Design C++11 demos        //
// Platform:    Dell XPS 2720 Touch, Win 8.1, Visual Studio 2013   //
// Author:      Jim Fawcett, CST 4-187, Syracuse Univesity         //
//              jfawcett@twcny.rr.com                              //
/////////////////////////////////////////////////////////////////////
/*
 *  std::map<key,value> is based on a balanced binary (red-black) tree
 *  with types key and value and is ordered on key comparisons
 */
#include "../Helpers/Helpers.h"
#include <unordered_map>
#include <string>
#include <iostream>

using namespace UtilityHelpers;

int main()
{
  using Test = ContainerHelpers;  // type alias
  using Key = int;
  using Value = std::string;

  try
  {
    Utilities::title("Demonstrating Maps Package", '=');

    // std::map contains a collection of key-value pairs.
    // You can initialize an unordered_map with a list of pairs.

    Utilities::title("demo std::map<int, std::string>");
    std::map<Key, Value> mapIntStr{
      { 0, "zero" }, { 1, "one" }, { 2, "two" }, { 3, "three" }, { 4, "four" }, { 5, "five" }, { 6, "six" }
    };
    Test::showPairs(mapIntStr);

    // maps use an indexing scheme for lookup.  

    std::string delim = "\"";
    Key key = 3;
    Value value = mapIntStr[key];
    std::cout << "\n  the fourth element of map has key: " << key << " and value " << delim << value << delim << "\n";

    // Be careful - if you index with a non-existant key it gets inserted with default constructed value.

    Key doesntExist = -1;
    value = mapIntStr[doesntExist];
    std::cout << "\n  undefined: key = " << doesntExist << ", and value = " << value;
    Test::showPairs(mapIntStr);

    // If you index with existing key you overwrite the old value.

    std::cout << "\n  inserting element { -1, \"minus one\" }";
    mapIntStr[doesntExist] = "minus one";
    Test::showPairs(mapIntStr);

    // Inserting new key-value pair

    std::cout << "\n  inserting element { 15, \"fifteen\" }";
    mapIntStr[15] = "fifteen";
    Test::showPairs(mapIntStr);

    // Inserting list of items

    std::cout << "\n  inserting list: { { 8, \"eight\" }, { 9, \"nine\" } }";
    mapIntStr.insert({ { 8, "eight" }, { 9, "nine" } });
    Test::showPairs(mapIntStr);

    // Erasing item with given key

    key = 8;
    std::cout << "\n  erasing item with key == " << key;
    mapIntStr.erase(key);
    Test::showPairs(mapIntStr);

    // std::map can have any key that has an order defined and can be copied and/or moved.
    // It can have any value that can be copied and/or moved.

    Utilities::title("demo std::map<std::string, int>");
    std::map<std::string, int> mapStrInt{
      { "zero", 0 }, { "one", 1 }, { "two", 2 }, { "three", 3 }, { "four", 4 }, { "five", 5 }, { "six", 6 }
    };
    Test::showPairs(mapStrInt);

    Utilities::title("demonstrate map::find");
    std::string search_key = "four";
    std::map<std::string, int>::iterator iter = mapStrInt.find(search_key);
    if (iter != mapStrInt.end())
      std::cout << "\n  found { " << iter->first << ", " << iter->second << " }";
    else
      std::cout << "\n  " << search_key << " is not in map";
    search_key = "fifteen";
    iter = mapStrInt.find(search_key);
    if (iter != mapStrInt.end())
      std::cout << "\n  found { " << iter->first << ", " << iter->second << " }";
    else
      std::cout << "\n  " << search_key << " is not in map";
  }
  catch (std::exception ex)
  {
    std::cout << "\n\n" << ex.what();
  }
  std::cout << "\n\n";
}
