/////////////////////////////////////////////////////////////////
//  vectorOfPolys1.cpp - demonstrates that derived class objects
//                       that are stored in stl containers get
//                       sliced to base objects by copy constructor
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
//  Base Blob class - objects don't say too much
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
//                              and are larger in size.
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
    cout << endl << (it->say()).c_str();
  }
  cout << endl;
}
//----< compare names of Blobs >-------------------------------

bool lessForBlobs(Blob& b1, Blob& b2)
{
  return (b1.name() < b2.name());
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
  cout << title<'='>("Demonstrates Slicing with STL Containers") << endl;
 
  cout << title<'-'>("A Blob Speaking") << endl;
  cout << Blob("Charley").say() << endl;
  cout << title<'-'>("A verboseBlob Speaking") << endl;
  cout << verboseBlob("Joe","Frank").say() << endl;

  vector<Blob> Blobs;
  Blobs.push_back(Blob("Charley"));

  // push_back will call base copy ctor to store in vector.
  // This slices verboseBlob to a Blob, as output demonstrates.

  Blobs.push_back(verboseBlob("Joe","Frank"));
  Blobs.push_back(Blob("Frank"));

  cout << title<'='>("Blobs Speaking from vector<Blob> Container") << endl;
  cout << title<'-'>("Original Blob Order - where's verbousBlob?");
  show(Blobs);
  sort(Blobs.begin(),Blobs.end(),lessForBlobs);  // call ambiguous for less
  cout << title<'-'>("Sorted Blob Order - not here either!");
  show(Blobs);
  cout << endl;

  cout << title<'='>("Message:",UPPER) << endl;
  cout << "\n  Non-Polymorphic operation with container of objects."
       << "\n  Derived objects get sliced to base objects on copy in."
       << "\n\n";  
}
