#ifndef NONVIRTUALINTERFACE
#define NONVIRTUALINTERFACE
/////////////////////////////////////////////////////////////////////
// nonVirtualInterface.h - demonstrate NVI pattern                 //
//                                                                 //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2005       //
/////////////////////////////////////////////////////////////////////
/*
 * - Interface defines a contract between client and class hierarchy
 * - virtual functions provide an interface for derived classes that
 *   allow them to change the implementation of the base.
 * - Sometimes these two things - contract and modification of 
 *   implementation - need different treatment, perhaps different
 *   arguments.  Perhaps you may need to change the interface to the
 *   derived classes but if you have lots of users it would be
 *   disasterous to change the public interface.
 * - The Non Virtual Interface pattern nicely resolves this design
 *   tension.
 */
#include <iostream>

class nonVirtInterf
{
public:
  void doSomeThing()
  {
    std::cout 
      << "\n  doing something by calling private virtual functions";
    doFirstThing();
    doSecondThing();
  }
  virtual ~nonVirtInterf() {}
private:
  virtual void doFirstThing()
  {
    std::cout << "\n  doing base first thing";
  }
  virtual void doSecondThing()
  {
    std::cout << "\n  doing base second thing";
  }
};

class derivedNVI : public nonVirtInterf
{
private:
  virtual void doFirstThing()
  {
    std::cout << "\n  doing derived first thing";
  }
  virtual void doSecondThing()
  {
    std::cout << "\n  doing derived second thing";
  }
};

#endif
