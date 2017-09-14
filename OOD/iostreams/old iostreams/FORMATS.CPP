///////////////////////////////////////////////////////////
// formats.cpp                                           //
//   demonstrate ios formating                           //
//                                                       //
// Jim Fawcett, 3/24/96                                  //
///////////////////////////////////////////////////////////

#include <iostream>
#include <iomanip>

using namespace std;

void main() {


///////////////////////////////////////////////////////////////
// flags:                                                    //
//   skipws  showbase showpoint uppercase   showpos          //
//  unitbuf     stdio                                        //
///////////////////////////////////////////////////////////////
//  basefield:                                               //
//    dec       hex       oct                                //
///////////////////////////////////////////////////////////////

  cout << "\n====< formating integers >====\n";
  long save = cout.flags();    // save format state
  cout.setf(ios::showbase|ios::uppercase);
  cout << "  " << 59 << " in hexadecimal is "
       << hex  << 59 << dec << endl
       << "  " << 59 << " in octal is       "
       << oct  << 59 << dec << endl;
  cout.flags(save);            // restore original format state


///////////////////////////////////////////////////////////////////
// function:                                                     //
//     width()     width(n)       fill()      fill(n)            //
// precision() precision(n)                                      //
///////////////////////////////////////////////////////////////////
// floatfield:                                                   //
//  scientific        fixed    automatic                         //
///////////////////////////////////////////////////////////////////

  cout << "\n====< formating doubles >====\n";
  cout.precision(6);
  cout.setf(ios::right, ios::adjustfield);
  cout.setf(ios::scientific, ios::floatfield);
  cout.setf(ios::showpoint);
  double d = 3;
  int i;
  for(i=0; i<5; i++)
    cout << setw(14) << (d /= 3);
  cout << endl;
  cout.flags(save);

//
///////////////////////////////////////////////////////////////////
// adjustfield:                                                  //
//        left        right     internal                         //
///////////////////////////////////////////////////////////////////

  cout << "\n====< adjust, fill, and width >====\n";
  char *numbers[5] = { "zero", "one", "two", "three", "four" };
  int nums[5] = { 0, 1, 2, 3, 4 };
  cout.fill('.');
  for(i=0; i<5; i++) {
    cout.setf(ios::left, ios::adjustfield);
    cout << "  " << setw(30) << numbers[i];
    cout.setf(ios::right, ios::adjustfield);
    cout << setw(30) << nums[i] << endl;
  }
  cout.flags(save);

///////////////////////////////////////////////////////////////
// manipulators:                                             //
//   iostream.h -  dec, oct, hex, endl, ws, ends, flush,     //
//   iomanip.h  -                                            //
//     setfill(char), setw(int), setprecision(int),          //
//     setiosflags(long), resetiosflags(long)                //
///////////////////////////////////////////////////////////////

  cout << "\n====< manipulators >====\n";
  cout << "  " << setprecision(5) << (d = 1.0/3.0) << endl;
  cout << "  " << setfill('.') << setw(20) << d << endl;
  cout << "  " << setiosflags(ios::left | ios::showpos)
       << setw(20) << d << endl;
  cout << "  " << resetiosflags(ios::left | ios::showpos)
        << d << endl;
  cout.flags(save);
}