#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

void printVector(const std::vector<int>& numbers) {
    for(const auto& number : numbers) {
        std::cout << number << " ";
    }
    std::cout << std::endl;
}

int partition(std::vector<int>& numbers, int low, int high) {
    int pivot = numbers[high];

    int i = low - 1;

    for(int j = low; j <= high - 1; j++) {
        if(numbers[j] < pivot) {
            i++;
            std::swap(numbers[i], numbers[j]);
        }
    }
    swap(numbers[i + 1], numbers[high]);
    return (i + 1);
}

void QuickSort(std::vector<int>& numbers, int low, int high) {
    if(low >= high)
        return;

    int pi = partition(numbers, low, high);

    QuickSort(numbers, low, pi - 1);
    QuickSort(numbers, pi + 1, high);
}



void MyDescendingSort(std::vector<int>& numbers) {

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

        QuickSort(numbers, 0, numbers.size() - 1);
        printVector(numbers);
    }

    return 0;
}