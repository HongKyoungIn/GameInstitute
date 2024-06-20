#include <iostream>
#include <array>
#include <vector>

int main() {
    std::array<int, 10> arr = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    std::vector<int> arr2(2);

    std::cout << "arr max size " << arr.max_size() << std::endl;

    // arr[10]= 11; //Is OK? ^^a

    std::cout << "arr2 max size " << arr2.max_size() << std::endl;
    std::cout << "arr2.size() " << arr2.size() << std::endl;
    std::cout << "arr2.capacity() " << arr2.capacity() << std::endl;

    // arr2[10] = 11; //Is OK? ^^a

    arr2.push_back(12); //Is OK? YES!!!!

    std::cout << "arr2.size() " << arr2.size() << std::endl;
    std::cout << "arr2.capacity() " << arr2.capacity() << std::endl;


    std::vector<int> arr3;
    std::cout << "arr max size " << arr3.max_size() << std::endl;
    std::cout << "SIZE_MAX: " << std::numeric_limits<size_t>::max() << std::endl;

    return 0;
}