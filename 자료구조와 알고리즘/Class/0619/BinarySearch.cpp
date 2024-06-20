#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void printVector(const std::vector<int>& numbers) {
	for(const auto& number : numbers) {
		std::cout << number << " ";
	}
	std::cout << std::endl;
}

void BinarySearch(const std::vector<int>& numbers, const int target) {
	vector<int> temp = numbers;
	sort(temp.begin(), temp.end());

	int mid = numbers.size() / 2;
	int left = 0;
	int right = numbers.size();

	while(left <= right) {
		mid = (left + right) / 2;

		if(temp[mid] == target) {
			cout << mid << endl;
			break;
		}
		else if(temp[mid] > target)
			right = mid - 1;
		else
			left = mid + 1;
	}
	cout << mid << endl;
}

int main() {
	std::string input;
	std::vector<int> numbers;

	numbers.reserve(5);

	while(true) {
		std::getline(std::cin, input);

		std::istringstream iss(input);

		int number = 0;
		numbers.clear();

		while(iss >> number) {
			numbers.push_back(number);
		}

		std::cout << "capacity : " << numbers.capacity() << std::endl;
		std::cout << "size : " << numbers.size() << std::endl;

		if(0 == numbers.size()) break;

		printVector(numbers);

		BinarySearch(numbers, 10); // 타겟을 변경해 보세요.

	}

	return 0;
}