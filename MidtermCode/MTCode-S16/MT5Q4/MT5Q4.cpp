///////////////////////////////////////////////////////////////////////
// MT5Q4.cpp - Compound Object Operations                            //
//                                                                   //
// Jim Fawcett, CSE687 - Object Oriented Design, Midterm Spring 2016 //
///////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include "../Utilities/Utilities.h"

void putMsg(const std::string& msg)
{
  std::cout << "\n  " << msg.c_str();
}

class C
{
public:
  C() { putMsg("C default construction"); }
  C(const C& c) { putMsg("C copy construction"); }
  C& operator=(const C& c) { putMsg("C assignment"); }
  C(C&& c) { putMsg("C move construction"); }
  C& operator=(C&& c) { putMsg("C move assignment"); }
  ~C() { putMsg("C destruction"); }
};
/*
*  B's constructors, as their first act, invoke a C constructor.  They
*  don't execute their bodies until C's construction completes.
*/
class B
{
public:
  B() { putMsg("B default construction"); }
  B(const B& b) : c(b.c) { putMsg("B copy construction"); }
  B& operator=(const B& b) { putMsg("B assignment"); c = b.c; }
  B(B&& b) : c(std::move(b.c)) { putMsg("B move construction"); }
  B& operator=(B&& b) { putMsg("B move assignment"); c = std::move(b.c); }
  virtual void say() { putMsg("B object speaking"); }
  virtual ~B() { putMsg("B destruction"); }
private:
  C c;
};

class U
{
public:
  U() { putMsg("U default construction"); }
  U(const U& u) { putMsg("U copy construction"); }
  U& operator=(const U& u) { putMsg("U assignment"); }
  U(U&& u) { putMsg("U move construction"); }
  U& operator=(U&& u) { putMsg("U move assignment"); }
  ~U() { putMsg("U destruction"); }
};
/*
*  D's constructors, as their first act, invoke a B constructor.  They
*  don't execute their bodies until B's construction completes.
*/
class D : public B
{
public:
  D() { putMsg("D default construction"); }
  D(const D& d) : B(d) { putMsg("D copy construction"); }
  D& operator=(const D& d) { putMsg("D assignment"); B::operator=(d); }
  D(D&& d) : B(std::move(d)) { putMsg("D move construction"); }
  D& operator=(D&& d) { putMsg("D move assignment"); B::operator=(std::move(d)); }
  void f(U& u) { putMsg("D using U"); }
  void say() { putMsg("D object speaking"); }
  ~D() { putMsg("D destruction"); }
};

struct Cosmetic {
  ~Cosmetic() { std::cout << "\n\n"; }
} cosmetic;

using namespace Utilities;
using Utils = StringHelper;

void fun1(B b)
{
  Utils::title("operations in fun1");
  b.say();
}

void fun2(B& b)
{
  Utils::title("operations in fun2");
  b.say();
}


int main()
{
  Utils::Title("MT4Q5 - Operations of Compound Object");
  putline();

  Utils::title("operatons resulting from first statement");
  B* pB = new D;
  putline();

  Utils::title("operatons resulting from second statement");
  fun1(*pB);
  putline();

  Utils::title("operatons resulting from third statement");
  fun2(*pB);
  putline();

  Utils::title("operations due to deleting pointer");
  delete pB;

  std::cout << "\n\n";
}
