///////////////////////////////////////////////////////////////
//  set1.cpp - demonstrate container basics                  //
//                                                           //
//  Jim Fawcett, modified 4/5/98                             //
///////////////////////////////////////////////////////////////

// disable truncation warnings
#pragma warning( disable : 4786 ) 

// include STL containers and services
#include <vector>
#include <set>
#include <string>
/////////////////////////////////////////////////////////////
//  #include <iterator>                                    //
//  STL containers declare their own simple iterators so,  // 
//  you won't need this unless you are doing fancy stuff   //
/////////////////////////////////////////////////////////////

#include <iostream>
using namespace std;

void main(int argc, char *argv[]) {

/////////////////////////////////////////////////////////////
// vector is an indexable, expandable collection of items  //
/////////////////////////////////////////////////////////////

  vector<string> vos;
  int i;
  for(i=1; i<argc; i++)
    vos.push_back(argv[i]);
  
  cout << "list of command line arguments in "
       << "arrival order:\n";

	///////////////////////////////////////
	//  declare and use vector iterator  //
	///////////////////////////////////////

  vector<string>::iterator vi;
  for(vi = vos.begin(); vi != vos.end(); vi++)
    cout << "  " << *vi << endl;

//

////////////////////////////////////////////
// set is an ordered collection of items  //
////////////////////////////////////////////

  set<string> sos;
  for(i=1; i<argc; i++)
    sos.insert(argv[i]);

  cout << "\nlist of command line arguments in "
       << "lexographic order:\n";

	////////////////////////////////////
	//  declare and use set iterator  //
	////////////////////////////////////

  set<string>::iterator si;
  for(si = sos.begin(); si != sos.end(); si++)
    cout << "  " << *si << endl;

  cout << "\nlist of command line arguments in "
       << "reverse lexographic order:\n";

  set<string>::reverse_iterator rsi;
  for(rsi = sos.rbegin(); rsi != sos.rend(); rsi++)
    cout << "  " << *rsi << endl;

}
