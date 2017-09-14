#ifdef TEST_MAPSUM
#include <string>
#include <unordered_map>
#include <iostream>

class MapSum {
public:
	MapSum(std::unordered_map<std::string, int> data);
	int sum(const std::string prefix);
private:
	std::unordered_map<std::string, int> data_;
};

MapSum::MapSum(std::unordered_map<std::string, int> data) : data_(data) {}

int MapSum::sum(const std::string prefix) {
	int sum = 0;
	for (auto entry : data_) {
		if (entry.first.size() < prefix.size())
			continue;
		if (entry.first.compare(0, prefix.size(), prefix) == 0)
			sum += entry.second;
	}
	return sum;
}

int main() {
	std::unordered_map<std::string, int> data{ { "apple", 3 }, { "apricot", 5 }, { "pear", 7 } };
	MapSum sum(data);
	std::cout << sum.sum("ap");
}

#endif