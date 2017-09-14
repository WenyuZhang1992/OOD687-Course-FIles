///////////////////////////////////////////////////////////////////////
//  animals.cpp - another demonstration of functors                  //
//                                                                   //
//  Jim Fawcett, CSE687, Spring 2001                                 //
///////////////////////////////////////////////////////////////////////

#include <iostream>
using namespace std;

//----< class templatized on functor arguments >-----------------------

template <class T> class animal {

  public:
    animal();
    void speak();

  private:
    T animalSpeak;
};

//----< constructor >----------------------------------------------

template <class T> 
animal<T>::animal() : animalSpeak() {  // calls void ctor of T
  
  cout << "\n  constructing an animal"; 
}

//----< member function using template argument functor >----------

template <class T> 
inline void animal<T>::speak() { animalSpeak(); }  // calls T::operator()


//----< dog functor >--------------------------------------------------

class dog {

  public:
    dog();
    void operator()();
};

//----< constructor >----------------------------------------------

dog::dog() { cout << "\n  constructing a dog"; }

//----< functor member >-------------------------------------------

void dog::operator()() {

  cout << "\n    I am a dog.  I often have fleas and smell badly";
}


//

//----< cat functor >--------------------------------------------------

class cat {

  public:
    cat();
    void operator()();
};

//----< constructor >----------------------------------------------

cat::cat() { cout << "\n  constructing a cat"; }

//----< functor member >-------------------------------------------

void cat::operator()() {

  cout << "\n    I am a cat.  I usually ignore my owner";
}


//----< demonstrate use of functors as template arguments >------------

void main() {

  cout << "\n  Demonstrating Templates and Functors "
       << "\n ======================================\n";

  animal<dog> myDog;
  myDog.speak();

  cout << "\n";

  animal<cat> myCat;
  myCat.speak();

  cout << "\n\n";
}
