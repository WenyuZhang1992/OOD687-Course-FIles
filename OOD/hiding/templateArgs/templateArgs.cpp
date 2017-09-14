/////////////////////////////////////////////////////////////////
//  templateArgs.cpp - demonstrate that template arguments
//                     have to be unambiguous
//
//  If we use the name less for comparison function and also
//  #include <functional> which defines name less, compiler
//  can't deduce which to use so compilation fails.
//
//  Jim Fawcett, CSE687 - Object Oriented Design, Spring 2003
/////////////////////////////////////////////////////////////////

#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
using namespace std;

class Blob
{
public:
  Blob(const std::string& name) { _name = name; }
  string say()
  {
    std::string temp = "  Hi: ";
    temp += _name;
    temp += " Blob here";
    return temp;
  }
  std::string& Name() { return _name; }

private:
  std::string _name;
};

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

// less is defined in std::functional, so if we
// #include <functional> and use the name less here
// we get an ambiguity and compilation fails

bool lessForBlobs(Blob& b1, Blob& b2)
{
  return (b1.Name() < b2.Name());
}

//
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

int main()
{
  cout << title<'='>("Problems with Ambiguity in Template Arguments");
  vector<Blob> Blobs;
  Blobs.push_back(Blob("Charley"));
  Blobs.push_back(Blob("Joe"));
  Blobs.push_back(Blob("Frank"));

  cout << title<'-'>("Original Blob Order");
  show(Blobs);
  sort(Blobs.begin(),Blobs.end(),lessForBlobs);  // call ambiguous for less
  cout << title<'-'>("Sorted Blob Order");
  show(Blobs);
  cout << endl;
}