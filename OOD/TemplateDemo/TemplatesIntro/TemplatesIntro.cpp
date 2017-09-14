/////////////////////////////////////////////////////////////////////
// TemplatesIntro.cpp - Demonstrate Template Syntax                //
//                                                                 //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2017       //
/////////////////////////////////////////////////////////////////////

#include "TemplatesIntro.h"
#include <iostream>
#include <functional>

/////////////////////////////////////////////////////////////////////
// Widget class - shows user defined types can be template arguments

class Widget
{
public:
  Widget(const std::string& str = "") : state(str) {}
  std::string& value() { return state; }
private:
  std::string state;
};

std::ostream& operator<<(std::ostream& out, Widget& widget)
{
  out << widget.value();
  return out;
}

std::istream& operator >> (std::istream& in, Widget& widget)
{
  std::string temp;
  while (in.good())  // extract all the words from widget's string state
  {
    in >> temp;
    widget.value() += temp + " ";
  }
  return in;
}

/////////////////////////////////////////////////////////////////////
// lambdas that provide mildly useful local processing

std::function<void()> putLine = []() { std::wcout << "\n"; };

std::function<void(size_t)> putLines = [](size_t n) {
  for (size_t i = 0; i < n; ++i)
    putLine();
};

std::function<void(const std::string&, char)> titleCore = [](const std::string& msg, char underline='-') {
  std::cout << "\n  " << msg.c_str();
  std::wcout << "\n " << std::string(msg.size() + 2, underline).c_str();
};

std::function<void(const std::string&)> Title = [](const std::string& msg) { titleCore(msg, '='); };

std::function<void(const std::string&)> title = [](const std::string& msg) { titleCore(msg, '-'); };

/////////////////////////////////////////////////////////////////////
// Demo code

int main()
{
  Title("Demonstrating Templates");
  putLine();

  title("TemplateDemo<int> and Convert<TemplateDemo<int>>");
  TemplateDemo<int> tdi(42);
  std::cout << "\n  type is:  " << Convert<TemplateDemo<int>>::id(tdi);
  std::cout << "\n  value is: " << tdi.value();
  std::string TDIstring = Convert<TemplateDemo<int>>::toString(tdi);
  std::cout << "\n  toString: " << TDIstring;
  std::cout << "\n  creating TemplateDemo object using fromString:";
  TemplateDemo<int> newTdi = Convert<TemplateDemo<int>>::fromString(TDIstring);
  std::cout << "\n  type is:  " << Convert<TemplateDemo<int>>::id(newTdi);
  std::cout << "\n  value is: " << newTdi.value();
  putLine();

  title("TemplateDemo<double> and Convert<TemplateDemo<double>>");
  TemplateDemo<double> tdd(3.1415927);
  std::cout << "\n  type is:  " << Convert<TemplateDemo<double>>::id(tdd);
  std::cout << "\n  value is: " << tdd.value();
  std::string TDDstring = Convert<TemplateDemo<double>>::toString(tdd);
  std::cout << "\n  toString: " << TDDstring;
  std::cout << "\n  creating TemplateDemo object using fromString:";
  TemplateDemo<double> newTdd = Convert<TemplateDemo<double>>::fromString(TDDstring);
  std::cout << "\n  type is:  " << Convert<TemplateDemo<double>>::id(newTdd);
  std::cout << "\n  value is: " << newTdd.value();
  putLine();

  title("TemplateDemo<Widget> and Convert<TemplateDemo<Widget>>");
  Widget widget("I am a widget");
  TemplateDemo<Widget> tdw(widget);
  std::cout << "\n  type is:  " << Convert<TemplateDemo<Widget>>::id(widget);
  std::cout << "\n  value is: " << tdw.value();
  std::string TDWstring = Convert<TemplateDemo<Widget>>::toString(tdw);
  std::cout << "\n  toString: " << TDWstring;
  std::cout << "\n  creating TemplateDemo object using fromString:";
  TemplateDemo<Widget> newTdw = Convert<TemplateDemo<Widget>>::fromString(TDWstring);
  std::cout << "\n  type is:  " << Convert<TemplateDemo<Widget>>::id(newTdw);
  std::cout << "\n  value is: " << newTdw.value();

  putLines(2);
}