///////////////////////////////////////////////////////////////
//  iter2a.cpp  - demonstrate stream iterators               //
//                ----------------------------               //
//                Reads words from the input stream and      //
//                writes to cout using stream iterators.     //
//                                                           //
//  Jim Fawcett, 4/4/98                                      //
///////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <string>

using namespace std;

void main(int argc, char *argv[]) {

  ifstream in(argv[argc-1]);
  if(!in.good() || argc == 1) {
    cout << "  can't open file " << argv[argc-1] << endl;
    return;
  }

  istream_iterator<string> inString(in);
  ostream_iterator<string> outString(cout);

  while(in.good()) {
    *outString++ = *inString++;
    cout << endl;
  }
  *outString = *inString;
}