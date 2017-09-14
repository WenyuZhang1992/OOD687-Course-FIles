//  remove1.cpp - Erase all the zero elements in a vector
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

  vector<int>::iterator it, tempIt;
  for(it=v.begin(); it!=v.end(); it++) {
    tempIt = it;
    if(*tempIt == 0)
      v.erase(tempIt);  // error here because erase invalidates 
  }                     // every iterator into the vector
  showVec(v);
}