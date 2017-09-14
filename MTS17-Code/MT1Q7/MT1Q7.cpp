/////////////////////////////////////////////////////////////////////
// MT1Q7 - Define Lambda                                           //
//                                                                 //
// Jim Fawcett, CSE687 - Midterm Solution, Spring 2017             //
/////////////////////////////////////////////////////////////////////

#include <functional>
#include <string>
#include <iostream>

std::function<void(std::string)> title = [](const std::string& msg) {
  std::cout << "\n  " << msg;
  std::cout << "\n " << std::string(msg.length() + 2, '-');
};

int main()
{
  title("MT1Q7 - create a lambda");
  std::cout << "\n  That's the demo folks!";
  std::cout << "\n\n";
}