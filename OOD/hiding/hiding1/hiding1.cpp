/////////////////////////////////////////////////////////////////
//  Hiding1.cpp - demonstrate simple hiding
//
//  Overloading is the use of the same function identifier
//  for different functions DECLARED IN THE SAME SCOPE.
//
//  A non virtual function is an invariant over the hierarchy
//  specified by the base class.
//
//  Here, I am paraphrasing:
//    Stephen Dewhurst, C++ Gotchas, Addison-Wesley, 2003
//
//  Jim Fawcett, CSE687 - Object Oriented Design, Spring 2003
/////////////////////////////////////////////////////////////////

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

/////////////////////////////////////////////////////////////////
//  base::process is overloaded in the base:: scope
//  - They are non-virtual and so should be invariant
//    over the entire hierarchy
//
class base
{
public:
  virtual ~base() {}
  void process(int x);
  void process(double d);
  virtual base& id();
};

inline base& base::id()
{
  cout << endl << setw(30) << "  base object invoking:";
  return *this;
}

inline void base::process(int i)
{
  cout << setw(30) << "  base::process(int i):" << "i = " << i;
}

inline void base::process(double d)
{
  cout << setw(30) << "  base::process(double d):" << "d = " << d;
}

//
/////////////////////////////////////////////////////////////////
//  derived1::process is not in base scope but attempts to
//  overload base process functions, so:
//  - The identifier process hides the overloaded
//    base::process functions
//  - derived1 objects cannot access the base process functions
//
class derived1 : public base
{
public:
  void process();         // hides base process functions
  derived1& id();
//  using base::process;  // this will unhide both base process members
};

inline derived1& derived1::id()
{
  cout << endl << setw(30) << "  derived1 object invoking:";
  return *this;
}

inline void derived1::process()
{
  cout << setw(30) << "  derived1::process()";
}

/////////////////////////////////////////////////////////////////
//  derived2 wisely does not attempt this overload, e.g., 
//  does not provide a process function, so:
//  - There is no hiding, and derived2 objects can access
//    the base::process functions.
//
class derived2 : public base
{
public:
  derived2& id();
  // no hiding here
};

inline derived2& derived2::id()
{
  cout << endl << setw(30) << "  derived2 object invoking:";
  return *this;
}

//
const int UPPER = true;
template <char ch>
string title(const string &t,bool upper=false)
{
  string underline(t.length()+2,ch);
  string temp;
  if(upper)
    temp = string("\n ") + underline + string("\n  ");
  else
    temp = string("\n  ");
  return temp + t + string("\n ") + underline;
}

int main()
{
  cout << 
    title<'='>("Problems trying to Overload Base Functions in Derived Class");
  cout.setf(ios::left,ios::adjustfield);
  cout.fill(' ');
  base b;
  b.id().process(3);
  b.id().process(3.5);

  derived1 d1;
  cout << endl;

  d1.id().process();
//  d1.id().process(3);
//  d1.id().process(3.5);
//  won't compile because process() hides base::process(int)
//  unless we uncomment using base::process; statement in class declaration.
  cout << endl;

  derived2 d2;
  d2.id().process(3);
  d2.id().process(3.5);

  cout << endl << 
    "\n  base provides non-virtual functions process(int) & process(double)\n";
  cout << "\n  derived1 attempts to provide overload process()"
       << "\n  which hides base process functions";
  cout << 
    "\n  so derived1 can't call base process functions - won't compile\n";
  cout << 
    "\n  derived2 did not attempt to overload process "
    "\n  so can call base process functions";
  cout << endl <<
    title<'='>("Message: don't attempt to overload base functions in derived class",UPPER);
  
  cout << "\n\n";
}
/////////////////////////////////////////////////////////////////
//  The Message:
//    Don't attempt to overload functions in a different scope.
//    It does not work!

