/////////////////////////////////////////////////////////////////
//  PTS.cpp - Issue #4 : partial template specialization       //
//                                                             //
//  Jim Fawcett, CSE687 - Object Oriented Design, Spring 2005  //
/////////////////////////////////////////////////////////////////
//  Partial Template Specialization:
//  Allows you to specialize a subset of a class's template
//  parameters.
//
//  Below we give an example of a smart pointer designed
//  to handle arrays of some fixed size, determined by the
//  integer template parameter.
//
//  For non-arrays we specialize the template for size=1,
//  leaving the type parameter T unspecified.

#include <string>
#include <iostream>

template <typename T, int size>
class smartPtr
{
public:
  smartPtr(T* pTr)
  {
    pTr_ = new T[size];
    for(int i=0; i<size; ++i)
      pTr_[i] = *pTr;
  }
  ~smartPtr() { delete [] pTr_; }
  T& operator*() { return *pTr_; }
  T operator[](int n) { return pTr_[n]; }
  // other members
private:
  T* pTr_;
};

template <typename T>
class smartPtr<T,1>
{
public:
  smartPtr(T* pTr) : pTr_(new T(*pTr)) {}
  ~smartPtr() { delete pTr_; }
  T& operator*() { return *pTr_; }
  // note that operator[] is not supplied
  // other members
private:
  T* pTr_;
};

void main()
{
  std::string s1 = "hi there";
  smartPtr<std::string,3> spArray(&s1);
  for(int i=0; i<3; ++i)
    std::cout << "\n  " << *spArray;
  std::cout << "\n  " << spArray[1];
  std::cout << "\n\n";

  std::string s2 = "hi there again";
  smartPtr<std::string,1> spNoArray(&s2);
  std::cout << "\n  " << *spNoArray;
  std::cout << "\n\n";
}
