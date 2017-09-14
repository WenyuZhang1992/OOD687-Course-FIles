/////////////////////////////////////////////////////////////////////
//  vectorOfPolys2.cpp
//    - demonstrates that pointers to derived class objects held 
//      by vector container support polymorphic calls, but require
//      client management of memory.
//
//  Jim Fawcett, CSE687 - Object Oriented Design, Spring 2003
/////////////////////////////////////////////////////////////////

#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
using namespace std;

///////////////////////////////////////////////////////////////
//  Base blob class - objects don't say too much
//
class Blob
{
public:
  Blob(const std::string& name)
  {
    _name = name;
  }
  virtual ~Blob() {}
  virtual std::string say()
  {
    std::string temp = "  Hi: ";
    temp += _name;
    temp += " here.";
    return temp;
  }
  std::string& name() { return _name; }

protected:
  std::string _name;
};

//
///////////////////////////////////////////////////////////////
//  Derived verboseBlob class - verbose objects say more
//                              and are larger in size
//
class verboseBlob : public Blob
{
public:
  verboseBlob(const std::string& name, const std::string& buddy) : Blob(name)
  {
    _buddy = buddy;
  }
  std::string say()
  {
    std::string temp = "  Hi there: I'm a blob and my name is ";
    temp += _name;
    temp += ".  My buddy here, is ";
    temp += _buddy + ".";
    return temp;
  }
  std::string& buddy() { return _buddy; }

private:
  std::string _buddy;
};
//
//----< display contents of container >------------------------

template<typename cont>
void show(cont &c)
{
  cont::iterator it;
  for(it=c.begin(); it!=c.end(); ++it)
  {
    cout << endl << ((*it)->say()).c_str();
  }
  cout << endl;
}
//----< compare names of Blobs >-------------------------------

bool lessForBlobs(Blob* pb1, Blob* pb2)
{
  return (pb1->name() < pb2->name());
}
//----< make fancy titles >------------------------------------

const int UPPER = true;
template <char ch>
string title(const string &t,bool upper=false)
{
  string underline(t.length()+2,ch);
  string temp;
  if(upper)
    temp = string("\n ") + underline + string("\n  ");
  else
    temp = string("\n  ");
  return temp + t + string("\n ") + underline;
}
//----< entry point >------------------------------------------

int main()
{
  cout << title<'='>("Avoid Slicing by Holding Pointers to Blobs") << endl;
  vector<Blob*> Blobs;
  Blobs.push_back(new Blob("Charley"));

  // push_back will copy base pointers which act polymorphically.
  // No more slicing!

  Blobs.push_back(new verboseBlob("Joe","Frank"));
  Blobs.push_back(new Blob("Frank"));

  cout << title<'-'>("Original Blob Order - here's verbousBlob!");
  show(Blobs);
  sort(Blobs.begin(),Blobs.end(),lessForBlobs);
  cout << title<'-'>("Sorted Blob Order - still here!");
  show(Blobs);
  cout << endl;
  vector<Blob*>::iterator it;
  for(it=Blobs.begin(); it!=Blobs.end(); ++it)
    delete *it;

  cout << title<'='>("Message:",UPPER) << endl;
  cout << "\n  Polymorphic operation with container of pointers"
       << "\n  but requires client to participate in memory management"
       << "\n\n";  
}
