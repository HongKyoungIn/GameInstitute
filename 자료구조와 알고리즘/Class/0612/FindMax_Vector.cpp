#include <iostream>
#include <array>
#include <vector>

using namespace std;

int FindMaxArray(const int* arr, const int size) {
    int max = arr[0];

    for(size_t i = 0; i < size; i++) {
        if(max < arr[i]) {
            max = arr[i];
        }
    }

    cout << "FindMaxArray : " << max << endl;
    return max;
}

template <size_t N>
int FindMaxNumStdArray(const std::array<int, N>& arr) {
    int max = arr[0];

    for(size_t i = 0; i < N; i++) {
        if(max < arr[i]) {
            max = arr[i];
        }
    }
    cout << "FindMaxNumStdArray : " << max << endl;
    return max;
}

int FindMaxNumStdVector(std::vector<int>& arr) {
    int max = arr[0];

    for(size_t i = 0; i < arr.size(); i++) {
        if(max < arr[i]) {
            max = arr[i];
        }
    }
    cout << "FindMaxNumStdVector : " << max << endl;
    return max;
}

int main() {
    int arr[10] = { 11, 2, 3, 4, 1, 4, 3, 2, 21 };
    std::array<int, 10> arr2 = { 11, 2, 3, 4, 1, 4, 3, 2, 22 };
    std::vector<int> arr3 = { 11, 2, 3, 4, 1, 4, 3, 2, 23 };

    FindMaxArray(arr, 10);
    FindMaxNumStdArray(arr2);
    FindMaxNumStdVector(arr3);

    

    return 0;
}