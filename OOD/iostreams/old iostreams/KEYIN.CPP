// keyin.cpp

//#include <iostreams.h>
#include <iomanip.h>
#include <fstream.h>

void main(int argc, char *argv[]) {

  ifstream in(argv[argc-1]);
  if(in.good())
    cout << "successfully opened " << argv[argc-1] << endl;
  else
    cout << "failed to open " << argv[argc-1] << endl;


/*
  char ch;
  int count;
  streambuf *sb = cin.rdbuf();
  do {
    cin.seekg(2, ios::beg);
    streampos sp = cin.tellg();
    *(char*)(sb+sp) = '\n';
    cin.seekg(0, ios::beg);
    cin >> ch;
    cout << ch << ':';
  } while(ch != 'q');
*/
//  char buf[1];
//  streambuf* sb = cin.rdbuf();
//  sb->doallocate();
//  while((ch = cin.get()) != 'q')
//    cout << ch;

}
