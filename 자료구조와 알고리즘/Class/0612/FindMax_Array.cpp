#include <iostream>

using namespace std;

int FindMax(const int* arr, const int size) {
    int max = arr[0];

    for(size_t i = 0; i < size; i++) {
        if(max < arr[i]) {
            max = arr[i];
        }
    }

    return max;
}

int main() {
    int arr[10] = { 11, 2, 3, 4, 1, 4, 3, 2, 22 };

    std::cout << "Max: " << FindMax(arr, 10) << std::endl;

    return 0;
}