///////////////////////////////////////////////////////////////
//  iter1a.cpp  --  first STL iterator demo                  //
//                                                           //
//  Jim Fawcett, 4/4/98                                      //
///////////////////////////////////////////////////////////////

#include <vector>
#include <iostream>
#include <iomanip>
#include <math.h>
#include <complex>

using namespace std;

void main() {

  cout << "\n  Demonstrating Iterators "
       << "\n =========================\n";
  
  cout << "\n using std::complex\n";

  vector< complex<double> > vc;

  vc.push_back(complex<double>( 1, 0));
  vc.push_back(complex<double>( 1, 1));
  vc.push_back(complex<double>( 0, 1));
  vc.push_back(complex<double>(-1, 1));
  vc.push_back(complex<double>(-1, 0));
  vc.push_back(complex<double>(-1,-1));
  vc.push_back(complex<double>( 0,-1));
  vc.push_back(complex<double>( 1,-1));
  vc.push_back(complex<double>( 1, 0));

  const double pi = 3.1415927;
  vector< complex<double> >::iterator vci;
  double angle;

  for(vci=vc.begin(); vci != vc.end(); vci++) {
    angle = atan2(vci->imag(),vci->real())*(180.0/pi);
    cout << "  " << "("
         << setw(2) << (*vci).real() << ","
         << setw(2) << (*vci).imag() << ")"
         << setw(6) << angle << "\n";
  }
  cout << endl;
}
