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


void MyAscendingSort(std::vector<int>& numbers) {
    int count = 0;

    for(int j = 0; j < numbers.size(); j++) {

        for(int i = 0; i < numbers.size() - 1; i++) {
            int temp = 0;
            if(numbers[i] > numbers[i + 1]) {
                temp = numbers[i];
                numbers[i] = numbers[i + 1];
                numbers[i + 1] = temp;
                count++;
            }
        }
    }

    cout << "count : " << count << endl;
}

void MyDescendingSort(std::vector<int>& numbers) {
    int count = 0;

    bool swapped;
    for(int j = 0; j < numbers.size() - 1; j++) {
        swapped = false;
        for(int i = 0; i < numbers.size() - 1 - j; i++) {
            if(numbers[i] < numbers[i + 1]) {
                std::swap(numbers[i], numbers[i + 1]);
                swapped = true;
                count++;
            }
        }
        // If no two elements were swapped by inner loop, then break
        if(!swapped) break;
    }
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

        MyAscendingSort(numbers);
        printVector(numbers);

        cout << endl;

        MyDescendingSort(numbers);
        printVector(numbers);

    }

    return 0;
}