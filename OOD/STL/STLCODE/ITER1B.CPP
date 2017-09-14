///////////////////////////////////////////////////////////////
//  iter1b.cpp  --  first STL iterator demo                  //
//                                                           //
//  compiles with Visual C++ 5.0                             //
//  won't compile with Borland 5.0                           //
//  Jim Fawcett, 4/4/98                                      //
///////////////////////////////////////////////////////////////

#include <vector>
#include <utility>
#include <iostream>
#include <iomanip>
#include <math.h>

using namespace std;

void main() {

  cout << "  using pair defined in std::utility\n";

  vector< pair<double,double> > vc;
  vc.push_back(pair<double,double>( 1, 0));
  vc.push_back(pair<double,double>( 1, 1));
  vc.push_back(pair<double,double>( 0, 1));
  vc.push_back(pair<double,double>(-1, 1));
  vc.push_back(pair<double,double>(-1, 0));
  vc.push_back(pair<double,double>(-1,-1));
  vc.push_back(pair<double,double>( 0,-1));
  vc.push_back(pair<double,double>( 1,-1));
  vc.push_back(pair<double,double>( 1, 0));

  const double pi = 3.1415927;
  vector< pair<double,double> >::iterator vci;
  double angle;

  for(vci=vc.begin(); vci != vc.end(); vci++) {
    angle = atan2(vci->second,vci->first)*(180.0/pi);
    cout << "  " << "("
         << setw(2) << (*vci).first << ","
         << setw(2) << (*vci).second << ")"
         << setw(6) << angle << "\n";
  }
  cout << endl;
}