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
    for(int i = 0; i < numbers.size(); i++) {
        int index = i;
        int min = numbers[i];

        for(int j = i + 1; j < numbers.size(); j++) {
            if(min >= numbers[j]) {
                min = numbers[j];
                index = j;
            }
        }
        swap(numbers[i], numbers[index]);
    }
    cout << "-오름차순 정렬-" << endl;
}

void MyDescendingSort(std::vector<int>& numbers) {
    for(int i = 0; i < numbers.size(); i++) {
        int index = i;
        int max = numbers[i];

        for(int j = i + 1; j < numbers.size(); j++) {
            if(max < numbers[j]) {
                max = numbers[j];
                index = j;
            }
        }
        swap(numbers[i], numbers[index]);
    }
    
    cout << "- 내림차순 정렬 - " << endl;
}

void Sort(std::vector<int>& numbers) {
    int temp = 0;
    for(int i = 0; i < numbers.size(); ++i) {
        int indexMin = i;
        for(int j = i + 1; j < numbers.size(); ++j) {
            if(numbers[j] < numbers[indexMin]) {
                indexMin = j;
            }
        }
        temp = numbers[indexMin];
        numbers[indexMin] = numbers[i];
        numbers[i] = temp;
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

        Sort(numbers);
        printVector(numbers);

        /*MyDescendingSort(numbers);
        printVector(numbers);*/

        cout << endl;

    }

    return 0;
}