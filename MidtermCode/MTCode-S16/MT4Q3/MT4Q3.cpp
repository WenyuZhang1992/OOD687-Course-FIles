///////////////////////////////////////////////////////////////////////
// MT4Q3.cpp - Duplicates Lambda                                     //
//                                                                   //
// Jim Fawcett, CSE687 - Object Oriented Design, Midterm Spring 2016 //
///////////////////////////////////////////////////////////////////////

#include <iostream>
#include <iomanip>
#include <string>
#include <unordered_map>
#include <functional>
#include "../Utilities/Utilities.h"

struct Person
{
  std::string firstName;
  std::string lastName;
  std::string city;
};

void showPerson(Person person)
{
  std::cout << "\n  ";
  std::cout << std::setw(10) << person.firstName;
  std::cout << std::setw(15) << person.lastName;
  std::cout << std::setw(10) << person.city;
}

using namespace Utilities;
using Utils = StringHelper;
/*
 *  Note:  I'm finding people who live in the same city 
 *         instead of having the same last name.
 *
 *         The code is essentially the same.
 *         Just substitute last name where I've used city.
 *
 *         I think this example is more interesting.
 */
int main()
{
  Utils::Title("MT4Q3 - Finding same city dwellers");
  putline();

  Utils::title("Collecting People");
  using People = std::vector<Person*>;
  People people;

  Person tomSmith;
  tomSmith.firstName = "Tom";
  tomSmith.lastName = "Smith";
  tomSmith.city = "New York";
  showPerson(tomSmith);
  people.push_back(&tomSmith);

  Person MichaelBloomberg;
  MichaelBloomberg.firstName = "Michael";
  MichaelBloomberg.lastName = "Bloomberg";
  MichaelBloomberg.city = "New York";
  showPerson(MichaelBloomberg);
  people.push_back(&MichaelBloomberg);

  Person JimFawcett;
  JimFawcett.firstName = "Jim";
  JimFawcett.lastName = "Fawcett";
  JimFawcett.city = "Syracuse";
  showPerson(JimFawcett);
  people.push_back(&JimFawcett);

  Person StatueOfLiberty;
  StatueOfLiberty.firstName = "Statue";
  StatueOfLiberty.lastName = "OfLiberty";
  StatueOfLiberty.city = "New York";
  showPerson(StatueOfLiberty);
  people.push_back(&StatueOfLiberty);

  Person JimBehoeme;
  JimBehoeme.firstName = "Jim";
  JimBehoeme.lastName = "Boehiem";
  JimBehoeme.city = "Syracuse";
  showPerson(JimBehoeme);
  people.push_back(&JimBehoeme);

  Person JackTheRipper;
  JackTheRipper.firstName = "Jack";
  JackTheRipper.lastName = "TheRipper";
  JackTheRipper.city = "London";
  showPerson(JackTheRipper);
  people.push_back(&JackTheRipper);

  Person LucretiaBorgia;
  LucretiaBorgia.firstName = "Lucretia";
  LucretiaBorgia.lastName = "Borgia";
  LucretiaBorgia.city = "Venice";
  showPerson(LucretiaBorgia);
  people.push_back(&LucretiaBorgia);
  
  putline();
  
  Utils::title("Showing same city dwellers");

  ///////////////////////////////////////////////////////////////////
  // Solution starts here

  std::function<void(People&)> f = [](People& people)
  {
    using City = std::string;

    std::unordered_map<City, People> collectDups;

    for (auto pPerson : people)
    {
      collectDups[pPerson->city].push_back(pPerson);
    }

    for (auto item : collectDups)
    {
      People temp = item.second;
      if (temp.size() > 1)
      {
        for (auto pPerson : temp)
          showPerson(*pPerson);
      }
    }
  };

  // Solution ends here
  ///////////////////////////////////////////////////////////////////

  f(people);
  std::cout << "\n\n";
}