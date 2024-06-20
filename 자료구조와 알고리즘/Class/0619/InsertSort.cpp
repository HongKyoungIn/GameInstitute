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
    for(int i = 1; i < numbers.size(); i++) {
        for(int j = i - 1; j >= 0; j--) {
            if(numbers[j] > numbers[i]) {
                swap(numbers[j], numbers[i]);
                i--;
            }
            else {
                break;
            }
        }
    }

    cout << "- 오름차순 정렬 - " << endl;
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

        /*MyDescendingSort(numbers);
        printVector(numbers);*/

        cout << endl;

    }

    return 0;
}