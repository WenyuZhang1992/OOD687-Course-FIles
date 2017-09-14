/////////////////////////////////////////////////////////////////
// printElem.cpp - demonstrates use of functions and functors  //
//                 with an STL algorithm                       //
//                                                             //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2003   //
/////////////////////////////////////////////////////////////////

#include <list>
#include <iostream>
#include <algorithm>
using namespace std;

//----< unary function >-----------------------------------------

void printElem(int val) 
{
  cout << "\n  value is: " << val;
}

//----< unary function template >--------------------------------

template <typename T>
void printElemTemplate(T& val) 
{
  cout << "\n  value is: " << val;
}

// The following declaration is needed to force an instantiation
// of function since use of function pointer will not do that

template void printElemTemplate<int>(int &val);

//----< unary functor template ----------------------------------
//
//      allows defining the output stream
//
template <typename T>
class printElemFunctor : public unary_function<T,bool>
{
public:
  printElemFunctor(std::ostream &out = cout) : _out(out) {};
  void operator()(T& val)
  {
    _out << "\n  value is: " << val;
  }
private:
  ostream &_out;
};

//----< generic function to print elements of container >--------

template <typename C>
void printContainer(C& c)
{
  for_each(c.begin(), c.end(), printElemTemplate<C::value_type>);
}
//
void main( )
{
  list< int > li;
  li.push_back(1);
  li.push_back(2);
  li.push_back(3);
  li.push_back(2);
  li.push_back(1);
  li.push_back(0);
  li.push_back(-1);

  // unary function pointer used in algorithm
  for_each(li.begin(), li.end(), printElem);
  cout << "\n\n";

  // unary function template pointer used in algorithm
  for_each(li.begin(), li.end(), printElemTemplate<int>);
  cout << "\n\n";

  // unary functor template temporary used in algorithm
  for_each(li.begin(), li.end(), printElemFunctor<int>());
  cout << "\n\n";

  // generic printing function using function template pointer
  printContainer(li);
  cout << "\n\n";
}
