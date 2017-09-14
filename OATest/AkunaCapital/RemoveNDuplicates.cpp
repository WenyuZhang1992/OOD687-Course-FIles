/*  Remove N Duplicates:                                                   
 *  Write a function to remove all values from a vector whcih appears exactly n times
 *  and return an array of remaining values sorted in ascending order
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

//-----< function to solve problem >--------------------------------------------------

vector<int> remove_n_duplicates(int n, vector<int> int_array)
{
	if (int_array.size() == 0)
		return int_array;

	// Sort the vector
	std::sort(int_array.begin(), int_array.end());
	std::vector<int>::iterator start = int_array.begin();
	std::vector<int>::iterator end = start;

	int count = 0;
	while (end != int_array.end()) {
		if (*end != *start) {
			start = end;
			continue;
		}
		count++;
		if (count == 3 && *(++end) != *start) {
			vector<int>::iterator temp = end;
			int_array.erase(start, --end);
			start = temp;
			end = start;
		}
		else {
			end++;
		}
	}

	return int_array;
}

//-----<test stub>--------------------------------------------------------------------

#ifdef TEST_REMOVENDUPLICATES

int main() {
	vector<int> int_array({ 4, 4, 4, 3, 2, 1, 1 });
	int_array = remove_n_duplicates(2, int_array);
	for (int i : int_array) {
		std::cout << i << std::endl;
	}
}

#endif // !TEST_REMOVENDUPLICATES