///////////////////////////////////////////////////////////////
// fileio.cpp - demonstrate fstreams                         //
//                                                           //
// Jim Fawcett, 24 Mar 96, modified 23 Mar 97                //
///////////////////////////////////////////////////////////////

#include <iostream>     // cout, <<
#include <fstream>      // ifstream(), <<, >>
#include <cstdlib>      // exit(1);
using namespace std;

void main(int argc, char *argv[]) {

  if(argc < 2) {
    cout << "\nplease enter name of text file on command line\n\n";
    exit(1);
  }
  const int bufSize = 80;
  char buffer[bufSize];

// create a scope with { } and define an input stream inside
// then read line-by-line and send to standard output
  {
    ifstream in(argv[argc-1]);
    if(!in.good()) {
      cout << "can't open file " << argv[argc-1] << endl;
      exit(1);
    }
    else
      cout << "\n====< processing file " << argv[argc-1]
           << " using istream::getline() >====\n\n";
    while(in.good()) {
      in.getline(buffer,bufSize);
      cout << buffer << endl;
    }
  }  // in goes out of scope and is destroyed

// define stream again at global level, get pointer to its
// filebuf and stream input directly to output

  cout << "\f\n====< processing file " << argv[argc-1]
       << " using filebuf::rdbuf() >====\n\n";
  ifstream in(argv[argc-1]);
  filebuf *bptr = in.rdbuf();    // get pointer to stream
  cout << bptr;                  // stream input to output
  in.close();                    // still in scope so close it

// open stream again, seek to end to find size, and backup
// half way, then send last half to stdout

  in.open(argv[argc-1]);         // open it again
  in.seekg(0, ios::end);         // go to end of file
  streampos sp = in.tellg();     // size = number of bytes from beg
  in.seekg(-sp/2, ios::end);     // go to middle
  in.getline(buffer,bufSize);    // go to next newline
  cout << "\n\n====< processing last half of this "
       << sp << " byte file >====\n\n";
  cout << in.rdbuf();            // output from that point to end
//

// stream state goes bad when attempting to read past end of file

  char ch;
  in >> ch;
  if(!in.good())
    cout << "\n\nattempting to read past EOF makes stream state"
         << " not good\n";

// can't read any more until we clear stream to good state

  in.clear();
  if(in.good())
    cout << "stream state good after clear()\n";
  in.seekg(-3,ios::end);         // back up to good char
  in >> ch;
  if(in.good())
    cout << "after backing up and reading " << ch
         << " stream state still good\n";
  in >> ch;
  if(!in.good())
    cout << "after reading EOF stream state not good again\n";

}
