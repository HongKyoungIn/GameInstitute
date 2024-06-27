#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

void PrintHint(std::vector<int> _numbers, int _low, int _high) {
    cout << "low : " << _numbers[_low] << ", " << "high : " << _numbers[_high] << endl;
}

void printVector(const std::vector<int>& numbers) {
    for(const auto& number : numbers) {
        std::cout << number << " ";
    }
    std::cout << std::endl;
}

void MergeSort(std::vector<int>& numbers, int low, int high) {
    PrintHint(numbers, low, high);

    if(low >= high) return;

    int mid = (low + high) / 2;
    MergeSort(numbers, low, mid);
    MergeSort(numbers, mid + 1, high);

    //Merge !!!
    std::vector<int> temp(numbers.size());
    int i = low;
    int j = mid + 1;
    int k = low;

    while(i <= mid && j <= high) {
        if(numbers[i] < numbers[j]) {
            temp[k++] = numbers[i++];
        }
        else {
            temp[k++] = numbers[j++];
        }
    }
    while(i <= mid) {
        temp[k++] = numbers[i++];
    }
    while(j <= high) {
        temp[k++] = numbers[j++];
    }
    for(int i = low; i <= high; i++) {
        numbers[i] = temp[i];
    }

    std::cout << "Merge : ";
    PrintHint(numbers, low, high);
    cout << endl;
}


void CountingSort(std::vector<int>& numbers) {
    int max = *std::max_element(numbers.begin(), numbers.end());
    int min = *std::min_element(numbers.begin(), numbers.end());
    int range = max - min + 1;

    std::vector<int> count(range), output(numbers.size());
    
    // 크기순으로 갯수 세는 반복문
    for(int i = 0; i < numbers.size(); i++) {
        count[numbers[i] - min]++;
    }
    cout << "count : "; printVector(count);

    for(int i = 1; i < count.size(); i++) {
        count[i] += count[i - 1];
    }
    cout << "count : "; printVector(count);

    for(int i = numbers.size() - 1; i >= 0; i--) {
        output[count[numbers[i] - min] - 1] = numbers[i];
        count[numbers[i] - min]--;

        cout << "[" << i << " 번째 반복문]" << endl;
        cout << "count: "; printVector(count);
        cout << "output : "; printVector(output);
    }
    cout << endl;

    for(int i = 0; i < numbers.size(); i++) {
        numbers[i] = output[i];
    }
    
}

int main() {
    std::string input;
    std::vector<int> numbers;

    // numbers.reserve(5);

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

        CountingSort(numbers);
        printVector(numbers);
    }

    return 0;
}