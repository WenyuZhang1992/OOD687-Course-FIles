///////////////////////////////////////////////////////////////
// strio.cpp - demonstrate strstreams                        //
//                                                           //
// Jim Fawcett, 24 Mar 96, modified 23 Mar 97                //
///////////////////////////////////////////////////////////////

#include <iostream>     // cout, <<
#include <strstream>    // istrstream(), ostrstream(), <<, >>

using namespace std;

void main() {

  cout << "\n\n====< reading from string >====\n\n";

  istrstream source("15 3.1415927 Now is the hour");
  cout << "  " << source.rdbuf() << endl;

  cout << "\n\n====< writing to internal buffer >====\n\n";

  ostrstream destin;       // automatically allocates buffer
  source.seekg(0);
  destin << source.rdbuf() << endl;
  cout << "  " << destin.rdbuf();

  cout << "\n\n====< writing to custom buffer >====\n\n";

  const int bufSize = 50;
  char custombuf[bufSize];
  ostrstream custom(custombuf, bufSize);
  source.seekg(0);                    // designer has to ensure
  custom << source.rdbuf() << ends;   // there is no buffer overrun
  cout << "  " << custombuf;          // -- strstream won't

  cout << "\n\n====< parsing input buffer >====\n\n";

  int i; double d; char savebuf[bufSize];
  source.seekg(0);
  source >> i >> d;
  cout << "  i = " << i << endl;
  cout << "  d = " << d << endl;
  int j;
  for(j=0; j<5; j++) {
    source >> savebuf;
    cout << "  savebuf = " << savebuf << endl;
  }
}
