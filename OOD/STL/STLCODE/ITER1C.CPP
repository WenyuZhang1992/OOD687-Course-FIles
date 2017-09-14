///////////////////////////////////////////////////////////////
//  iter1a.cpp  --  first STL iterator demo                  //
//                                                           //
//  compiles with Borland C++ 5.0                            //
//  does not compile with Visual C++ 5.0                     //
//  Jim Fawcett, 4/4/98                                      //
///////////////////////////////////////////////////////////////


#include <vector>
#include <iostream>
#include <iomanip>
#include <math.h>
#ifdef use_std_complex
  #include <complex>
#endif

using namespace std;

#ifndef use_std_complex
template<class T> class complex {

  public:
    complex(T real=0, T imag=0) : _real(real), _imag(imag) { }
    complex(const complex<T> &c) : _real(c._real), _imag(c._imag) { }
    ~complex() { }
//    T mag() { return sqrt(_real*_real + _imag*_imag); }
    T& real() { return _real; }
    T& imag() { return _imag; }
    complex<T>& operator=(const complex<T> &c) {
      _real = c._real; _imag = c._imag; return *this;
    }
    bool operator==(const complex<T> &c) {
      if(_real == c._real && _imag == c._imag) return true;
      return false;
    }
//    bool operator<(const complex<T> &c) { return (mag() < c.mag()); }

  private:
    T _real;
    T _imag;
};
#endif

void main() {

  #ifdef using_std_complex
    cout << " using std::complex\n";
  #else
    cout << "  user defined complex\n";
  #endif
  complex<double> dc;
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