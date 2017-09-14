#include <iostream>
#include <algorithm>
 
int main() {
  int array[] = { 23, 5, -10, 0, 0, 321, 1, 2, 99, 30 };
  int elements = sizeof(array) / sizeof(array[0]); 
  std::sort(array, array + elements);
  for (int i = 0; i < elements; ++i) 
     std::cout << array[i] << ' ';
}
