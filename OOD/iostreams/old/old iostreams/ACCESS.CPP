///////////////////////////////////////////////////////////////
// access.cpp - demonstrate accessibility                    //
//                                                           //
// Jim Fawcett, 3/24/96                                      //
///////////////////////////////////////////////////////////////

#include <iostream.h>

class B {

  public:
    B(int x, int y) : xprot(x), xpriv(y) { }
    void showValues();

  protected:
    int xprot;

  private:
    int xpriv;
};

void B::showValues() {

  cout << "  xprot = " << xprot << endl;
  cout << "  xpriv = " << xpriv << endl;
}

class D : public B {

  public:
    D(int x, int y) : B(x,y) { }

    int accessDerProt(D &d) { return d.xprot; }
//  int accessDerPriv(D &d) { return d.xpriv; }    not accessible
//  int accessBasProt(B &b) { return b.xprot; }    not accessible
//  int accessBasPriv(B &b) { return b.xpriv; }    not accessible
};

// note:
// - private data in base class is never accessible to deriveds
// - protected data in base class is accessible only through
//   object, reference, or pointer to derived class object,
//   but not directly from a base class object

void main() {

  B b(1,2);
  D d(3,4);
  D another_D(5,6);

cout << "\n====< from B::b >====\n";
  b.showValues();

cout << "\n====< from D::d >====\n";
  d.showValues();

cout << "\n====< accessing xprot from another D >====\n";
  another_D.showValues();
  cout << "  accessDerProt: " << d.accessDerProt(another_D) << endl;
}
