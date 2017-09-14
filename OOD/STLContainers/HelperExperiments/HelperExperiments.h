#ifndef HELPERSEXPERIMENTS_H
#define HELPERSEXPERIMENTS_H
/////////////////////////////////////////////////////////////////////
// HelperExperiments.h - Utilities for STL container demos         //
//                                                                 //
// Application: CSE687 - Object Oriented Design C++11 demos        //
// Platform:    Dell XPS 2720 Touch, Win 8.1, Visual Studio 2013   //
// Author:      Jim Fawcett, CST 4-187, Syracuse Univesity         //
//              jfawcett@twcny.rr.com                              //
/////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <unordered_map>
#include <array>
#include <algorithm>
#include <utility>

namespace UtilityHelpers
{
  ///////////////////////////////////////////////////////////////////////////
  // demonstrates scoped enumerations

  enum class ShowType { range_for, foreach_functor, foreach_lambda };

  std::string showEnumType(ShowType showType);

  ///////////////////////////////////////////////////////////////////////////
  // demonstrates definition of functor
  // - displays a collection's item followed by a comma if not the last item

  template<typename T> std::string format();  // forward declaration of formatting helper

  template<typename C>
  struct Show
  {
    Show(size_t size) : _size(size) {}
    void operator()(typename const C::value_type & t)  // operator() makes functor
    {
      std::string delimiter;  // each item of output is wrapped in delimiters, fore and aft

      delimiter = format<C::value_type>();

      std::cout << delimiter << t << delimiter;
      if (++_count < _size)
        std::cout << ", ";
    }
    size_t& count() { return _count; }
  private:
    static size_t _count;
    size_t _size;
  };

  template<typename C>
  size_t Show<C>::_count = 0;

  /////////////////////////////////////////////////////////////////////////
  // formatting helper for show
  // - define delimiter of strings ("\""), chars ("\'"), and everything else ("")
  // - see above for usage

  template<typename T>
  std::string format()
  {
    std::string delimiter;  // each item of output is wrapped in delimiters, fore and aft

    if (typeid(T) == typeid(std::string))
    {
      delimiter = "\"";
    }
    else if (typeid(T) == typeid(char))
    {
      delimiter = "\'";
    }
    else
    {
      delimiter = "";
    }
    return delimiter;
  }

  ///////////////////////////////////////////////////////////////////////////
  // Display sequence container contents
  // - demonstrates use of range-for, functor, and lambda
  // - all three methods are equivalent

  class TestContainers
  {
  public:
    //----< alternate equivalent ways to show contents of container >----

    template<typename C>
    static void show(const C& c, ShowType showType = ShowType::range_for)
    {
      if (c.size() > 0)
      {
        // display type of container and display method

        std::cout << "\n  contents of " << typeid(c).name();
        std::cout << "\n  using " << showEnumType(showType) << "\n    ";

        auto show = Show<C>(c.size());  // create instance of functor, equivalent to Show<C> show(c.size());

        switch (showType)
        {
          // show container contents with range-for

        case ShowType::range_for:
          for (auto& item : c)
          {
            show(item);
          }
          show.count() = 0;
          break;

          // show container contents with for_each algorithm and functor

        case ShowType::foreach_functor:
          std::for_each(begin(c), end(c), show);
          show.count() = 0;
          break;

          // show container contents with for_each algorithm and lambda

        case ShowType::foreach_lambda:  // declarations local to a case must be enclosed in a braced scope
        {
          auto l = [&show](const C::value_type& t)
          {
            show(t);  // equivalent to show.operator()(t);
          };
          std::for_each(begin(c), end(c), l);
          show.count() = 0;
          break;
        }
        default:
          throw(std::exception("unknow enumeration"));
        }
        std::cout << "\n";
      }
    }

    ///////////////////////////////////////////////////////////////////////
    // display associative container contents

    template<typename C>
    static void showKeyValues(const C& c)
    {
      std::string keyDelim = format<C::key_type>();
      std::string valueDelim = format<C::value_type>();

      for (auto item : c)
      {
        std::cout << "\n  { " << keyDelim << item.first << keyDelim << ", " << valueDelim << item.second << valueDelim << " }";
      }
      std::cout << "\n";
    }

    ///////////////////////////////////////////////////////////////////////
    // display associative container contents with iterator

    template<typename C>
    static void showKeyValuesWithIterator(const C& c)
    {
      std::string keyDelim = format<C::key_type>();
      std::string valueDelim = format<C::value_type>();

      for (auto iter = begin(c); iter != end(c); ++iter)  // iter's type is C::const_iterator
      {
        std::cout << "\n { " << keyDelim << iter->first << keyDelim << ", " << valueDelim << iter->second << valueDelim << " }";
      }
      std::cout << "\n";
    }

    ///////////////////////////////////////////////////////////////////////
    // display title with underscore

    static void title(const std::string& title, char underscore = '-')
    {
      std::string tempStr = "\n  " + title + "\n " + std::string(title.size() + 2, underscore);
      std::cout << tempStr;
      if (underscore == '=')
        std::cout << "\n";
    }
  };
}

#endif
