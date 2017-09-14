/////////////////////////////////////////////////////////////////////
// MT1Q5.cpp - MT1Q5, MT2Q6, MT3Q6, MT4Q2 - Compound Object        //
//                                                                 //
// Jim Fawcett, CSE687 - Midterm Solution, Spring 2017             //
/////////////////////////////////////////////////////////////////////

// MT1Q5 - move constructor
// MT2Q6 - move assignment
// MT3Q6 - copy assignment 
// MT4Q2 - copy constructor

#include <string>
#include <iostream>

/* 
  class C
 -----------------------------------------------------------------------
  An instance of C is composed by B.
  class C member has correct copy, assignment, and destruction semantics.
*/
class C
{
public:
  C(const std::string& msg = "class C") : msg_(msg) 
  {
    std::cout << "\n  construction of C";
  }
  void say() { std::cout << "\n  C says: " << msg_; }
private:
  std::string msg_;
};
/* 
  class B
 -----------------------------------------------------------------------
  Instances of B are used as bases of D.
  class B members have correct copy, assignment, and destruction semantics.
*/
class B
{
public:
  B(const C& c = C("class C"), const std::string& msg = "class B") : msg_(msg), c_(c) 
  {
    std::cout << "\n  construction of B";
  }
  virtual ~B() {}
  virtual void say() { 
    std::cout << "\n  B says: " << msg_;  
    c_.say();
  }
private:
  std::string msg_;   // copy of msg
  C c_;               // copy of c
};
/* 
  class A
 -----------------------------------------------------------------------
  Instances of A are aggregated by D.
  Class A member has correct copy, assignment, and destruction semantics.
*/
class A
{
public:
  A(const std::string& msg = "class A") : msg_(msg) {}
  void say() { std::cout << "\n  A says: " << msg_; }
private:
  std::string msg_;
};
/* 
  class D
 -----------------------------------------------------------------------
  Instances of D are compound objects, inheriting from B and aggregating A.
  Due to aggregation, the member pA does not have correct copy, assignment, and destruction semantics.
*/
class D : public B
{
public:
  D(const std::string& msg = "class D") : msg_(msg), pA(nullptr) 
  {
    std::cout << "\n  Default construction of D";
  }
  D(D&& d);
  D(const D& d);
  D& operator=(D&& d);
  D& operator=(const D& d);
  void addA() { pA = new A; }
  virtual void say()
  {
    std::cout << "\n  D says: " << msg_;
    B::say();
    if (pA)
      pA->say();
    else
      std::cout << "\n  instance of A not added";
  }
  virtual ~D() 
  {
    std::cout << "\n  destruction of D";
    delete pA; 
  }
private:
  std::string msg_;
  A* pA;
};
//----< move construction of D >-------------------------------------

D::D(D&& d) : B(std::move(d)), msg_(std::move(d.msg_)), pA(d.pA)
{
  std::cout << "\n  move construction of D";
  d.pA = nullptr;
}
//----< copy construction of D >-------------------------------------

D::D(const D& d) : B(d), msg_(d.msg_)
{
  std::cout << "\n  copy construction of D";
  if (d.pA)
    pA = new A(*d.pA);
  else
    pA = nullptr;
}
//----< move assignment of D >---------------------------------------

D& D::operator=(D&& d)
{
  std::cout << "\n  move assignment of D";
  if (this == &d) return *this;
  B::operator=(std::move(d));
  msg_ = std::move(d.msg_);
  if (pA)
    delete pA;
  pA = d.pA;
  d.pA = nullptr;
  return *this;
}
//----< copy assignment of D >---------------------------------------

D& D::operator=(const D& d)
{
  std::cout << "\n  copy assignment of D";
  if (this == &d) return *this;
  B::operator=(d);
  msg_ = d.msg_;
  if (pA)
    delete pA;
  if (d.pA)
    pA = new A(*d.pA);
  else
    pA = nullptr;
  return *this;
}
//----< function to test move construction - occurs on return >------

D returnD() 
{
  D d;
  return d; 
}
//----< function to test copy construction - occurs on call >--------

void acceptD(D d) 
{
  d.say(); 
}
//----< emit two new lines on program exit >-------------------------

struct cosmetic
{
  ~cosmetic() { std::cout << "\n\n"; }
} cosm;

int main()
{
  std::cout << "\n  MT1Q5 - Demonstrating Compound Object Operations";
  std::cout << "\n ==================================================";

  D d;
  std::cout << "\n\n  invoking D returnD()";
  d = returnD();
  std::cout << "\n";
  d.say();

  d.addA();
  std::cout << "\n\n  invoking acceptD(D d)";
  acceptD(d);
  std::cout << "\n";

  D newD;
  newD = d;
  newD.say();

  std::cout << "\n\n";
}
