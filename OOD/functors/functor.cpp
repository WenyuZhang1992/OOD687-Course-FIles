///////////////////////////////////////////////////////////////////////////
//  functor.cpp - demonstrate creation and use of functors               //
//                                                                       //
//  Note:                                                                //
//  A functor is an object of a class that acts like a function. You     //
//  use functors in places that you would use function pointers, but     //
//  functors are more elegant and are type safe.  We start out by        //
//  demonstrating how function pointers work, for comparison.            //
//                                                                       //
//  You can read about function pointers and functors in:                //
//  - Polymorphic Function Objects, Steve Dewhurst, C/C++ User's         //
//    Journal, Feb 2001                                                  //
//  - Function Objects, 5.9, The C++ Standard Library, N. Josuttis,      //
//    Addison Wesley, 1999                                               //
//  Jim Fawcett, CSE687, Spring 2002                                     //
//                                                                       //
///////////////////////////////////////////////////////////////////////////

#pragma warning(disable : 4786)
#include <iostream>     // cout, <<
#include <iomanip>      // setw
#include <algorithm>    // sort()
#include <vector>       // vector
#include <cstdlib>      // srand(), rand()
#include <time.h>       // time()
using namespace std;

///////////////////////////////////////////////////////////////////////////
//  The function on this page illustrates use of FUNCTION POINTERS       //
///////////////////////////////////////////////////////////////////////////

//  forward function declaration

void showVec(vector<int>&, const std::string&);

//----< silly function used to demo function pointers >------------------
//
//  This function introduces the use of function pointers and
//  is demonstrated at the beginning of main(), below.  Its 
//  second argument is a function pointer, so it is a function
//  taking a function pointer as one of its arguments.  The
//  syntax:
//            void (*pFun)(vector<int> &vec);
//
//  declares pFun to be a pointer to a function with the
//  signature:
//            void someFunction(vector<int> &vec);
//
void fillAndShow(
       vector<int> &vec,                // vector of integers
       void (*pFun)(vector<int> &vec),  // pointer to a function
       const std::string &msg           // string message
     ) {

  pFun(vec);          // using function pointer to fill vector
  showVec(vec,msg);   // function to display vector contents
}

//
///////////////////////////////////////////////////////////////////////////
//  The classes on this page illustrate the use of FUNCTORS              //
///////////////////////////////////////////////////////////////////////////

//----< prodFunct returns product of its argument with stored value >----
//
//  This simple functor enjoys no advantages over the operator *
//  But it does illustrate that any class implementing the C++
//  operator() can use function syntax, as shown near the beginning
//  of main().

template <class T>
class productFunctor {

public:
  T operator()(const T &x, const T &y);
};

template <class T>
inline T productFunctor<T>::operator()(const T &x, const T &y) { 
  
  cout << "\n  product of " << x << " and " << y << " is " << x*y; 
  return x*y; 
}

//----< compFunct returns comparison of its two arguments >--------------
//
//  This functor illustrates that a functor can behave like a function,
//  but be significantly more powerful.  compFunc implements a comparison 
//  operation that can be any of the operators <, <=, ==, !=, >=, > simply 
//  by calling a member function setType(operationType).  This allows us 
//  to pass a sorting function the argument compFunc and then sort in 
//  either ascending or decending order, based on a run-time decision.

template <class T>
class compFunct {

  public:
    
    enum operationType { lt, lteq, eq, noteq, gteq, gt }; 

    compFunct() : _ot(eq) { }
    bool operator() (const T &x, const T &y);
    void setType(operationType ot) { _ot = ot; }
    std::string type();
    void display(const T&, const T&, const std::string&);

  private:
    operationType _ot;
};

/////////////////////////////////////////////////////////////////////////
//  This is a good point to drop down to the main() function and see   //
//  how the compFunct functor is used.  Then come back and proceed to  //
//  find out how each of its parts work.  You might first build and    //
//  run this program to see what its output looks like, then move on   //
//  to main().
/////////////////////////////////////////////////////////////////////////

//
//----< here's the function call operator overload >---------------------
//
//  This member function is what is needed to specialize
//  a class to a functor.  It endows instances of the 
//  class with function call syntax, as shown in main().

template <class T>
inline bool compFunct<T>::operator()(const T &x, const T &y) { 
  
  switch (_ot) {
    case lt    : return x<y;
    case lteq  : return x<=y;
    case eq    : return x==y;
    case gteq  : return x>=y;
    case gt    : return x>y;
    case noteq : return x!=y;
    default    : throw  "undefined operation type";
  }
  return true;
}

//----< type returns string description of the operation >---------------
//
//  This member function is here simply to support the display
//  needs of this specific demonstration.

template <class T>
inline std::string compFunct<T>::type() { 
  
  switch (_ot) {
    case lt    : return "\"less than\"";
    case lteq  : return "\"less than or equal to\"";
    case eq    : return "\"equal to\"";
    case gteq  : return "\"greater than or equal to\"";
    case gt    : return "\"greater than\"";
    case noteq : return "\"not equal to\"";
    default    : throw  "\"undefined operation type\"";
  }
  return "should not get here\"";
}

//----< displays the operands and type of operator used >----------------
//
//  More support for the specific display needs of this demo

template <class T> 
void compFunct<T>::display(const T &x, const T &y, const string &verb) {

  cout << "\n  " << x << verb.c_str() << type().c_str() << ' ' << y; 
}

//
/////////////////////////////////////////////////////////////////////
//  The global functions defined on this page support the handling
//  of containers of integers, used to demonstrate how compFunct
//  functor works.

//----< fill vector with random integers in [0,999] >--------------------

void fillRand(vector<int> &vec) {

  vec.erase(vec.begin(),vec.end());
  srand( (unsigned)time( NULL ) );
  for(int i=0; i<10; i++)
    vec.push_back((1000*rand())/RAND_MAX);
}

//----< fill vector with ascending sequence of integers >----------------

void fillSeq(vector<int> &vec) {

  vec.erase(vec.begin(),vec.end());
  for(int i=0; i<10; i++)
    vec.push_back(i);
}

//----< sort using STL sort algorithm >----------------------------------

void vecSort(vector<int> &vec, compFunct<int> compare) {

  sort(vec.begin(), vec.end(), compare);
}

//----< a templatized sort routine - same functionality as above >-------

template <compFunct<int>::operationType type>
void newVecSort(vector<int> &vec) {

  compFunct<int> compare;
  compare.setType(type);
  sort(vec.begin(), vec.end(), compare);
}

//----< display the contents of a vector of integers >-------------------

void showVec(vector<int> &vec, const std::string &msg = "") {

  if(msg.size() > 0)
    cout << "\n\n  " << msg.c_str() << "\n  ";
  else
    cout << "\n\n  ";
  for(int i=0; i<vec.size(); i++)
    cout << setw(4) << vec[i];
}

//
//----< test functor operations >----------------------------------------

using namespace std;

void main() {

  cout << "\n  Demonstrating Function Pointers "
       << "\n =================================";

  /////////////////////////////////////////////////////////////
  //  We are passing the function fillAndShow a vector of ints
  //  and a pointer to a function that will fill the vector.
  //  Two such functions are provided, fillRand, and fillSeq.

  vector<int> vec;
  fillAndShow(vec, fillRand, "using pointer to random fill function");
  fillAndShow(vec, fillSeq, "using pointer to sequential fill function");
  cout << '\n';

  cout << "\n  Demonstrating Functors "
       << "\n ========================\n";

  ///////////////////////////////////////////////////////////////
  //  productFunctor computes the product of its arguments
  //  You could easily write a simpler global function to do
  //  what this functor does.
  
  cout << "\n  First, a simple functor to compute a product: "
       << "\n -----------------------------------------------";

  productFunctor<double> product;
  cout << "\n    product returned = " << product(2.5,3) << "\n";

//
  ///////////////////////////////////////////////////////////////
  //  Comparison functor provides <, <=, ==, !=, >=, > operations
  //  It would be messy to write a single global function that
  //  does what this functor does.
  
  cout << "\n  Second, a functor to compare two values: "
       << "\n ------------------------------------------";

  compFunct<double> compare;

  double x=2, y=3.1415927;

  for(int i=0; i<6; i++) {

    // set operation type, e.g., <, <=, ==, !=, >=, >

    compare.setType((compFunct<double>::operationType)i);

    // Do comparison with one of those operators.
    // We built this functor to support the nice syntax
    // compare(x,y)

    if(compare(x,y))
      compare.display(x,y," is ");
    else
      compare.display(x,y," is not ");
  }
  cout << '\n';

  // Now we can pass compare to a sorting routine.

  cout << "\n  Here we use the compare functor to sort: "
       << "\n ------------------------------------------";

  vector<int> test;
  fillRand(test);
  showVec(test,"a random set of integers in [0,999]");
  compFunct<int> intCompare;
 
  // First in ascending order:
  
  intCompare.setType(compFunct<int>::lt);
  vecSort(test,intCompare);
  showVec(test,"after sorting in ascending order with compFunct::lt");

  // Now sort in descending order:

  intCompare.setType(compFunct<int>::gt);
  vecSort(test,intCompare);
  showVec(test,"after sorting in descending order with compFunct::gt");
  cout << '\n';

  // Use template function structure to ensure that client software
  // will use the compFunct<T> functor.

  cout << "\n  Here we use compFunct functor in template sort function: "
       << "\n ----------------------------------------------------------";

  std::string msg = "after ascending order sort with template argument\n";
  msg += "  compFunct<int>::operationType";
  newVecSort< compFunct<int>::lt >(test);
  showVec(test, msg);
  cout << '\n';

  cout << "\n\n";
}
