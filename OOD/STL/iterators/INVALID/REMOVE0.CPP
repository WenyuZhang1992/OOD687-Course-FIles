//  remove0.cpp - Erase all the zero elements in a vector
//                ILLUSTRATION OF WHAT DOES NOT WORK !!!

#include <vector>
#include <iostream>
using namespace std;

void showVec(const vector<int> &v) {

  cout << "\n  ";
  int i;
  for(i=0; i<v.size()-1; i++)
    cout << v[i] << ", ";
  cout << v[v.size()-1] << "\n\n";

}

void main() {

  vector<int> v;
  v.push_back(5);
  v.push_back(1);
  v.push_back(0);
  v.push_back(-1);
  v.push_back(0);
  v.push_back(3);
  v.push_back(0);
  v.push_back(0);
  v.push_back(-4);
  v.push_back(0);
  showVec(v);
  cout << "v.size()     = " << v.size()     << '\n';
  cout << "v.max_size() = " << v.max_size() << '\n';

  vector<int>::iterator it;
  for(it=v.begin(); it!=v.end(); it++)
    if(*it == 0)
      v.erase(it);  // error here because first 
                    // erase invalidates iterator
  showVec(v);
}