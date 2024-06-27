#include <iostream>
#include <vector>

int partition(std::vector<std::pair<int, char>>& arr, int low, int high) {
    //마지막을 피봇으로 합시다.
    int pivot = arr[high].first;

    int i = (low - 1);

    for(int j = low; j <= high - 1; j++) {
        if(arr[j].first < pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);

    return (i + 1);
}

void quickSort(std::vector<std::pair<int, char>>& arr, int low, int high) {
    if(low >= high) return; //base condition!

    int pi = partition(arr, low, high);

    quickSort(arr, low, pi - 1);
    quickSort(arr, pi + 1, high);
}

void MergeSort(std::vector<std::pair<int, char>>& arr, int low, int high) {
    if(low >= high) return;

    int mid = (low + high) / 2;
    MergeSort(arr, low, mid);
    MergeSort(arr, mid + 1, high);

    //Merge !!!
    std::vector<std::pair<int, char>> temp(arr.size());
    int i = low;
    int j = mid + 1;
    int k = low;

    while(i <= mid && j <= high) {
        if(arr[i].first <= arr[j].first)  // 작거나 같을 경우로 수정.
        {
            temp[k++] = arr[i++];
        }
        else {
            temp[k++] = arr[j++];
        }
    }

    while(i <= mid) {
        temp[k++] = arr[i++];
    }

    while(j <= high) {
        temp[k++] = arr[j++];
    }

    for(int i = low; i <= high; i++) {
        arr[i] = temp[i];
    }
}


int main() {
    std::vector<std::pair<int, char>> arr1 = { {4, 'a'}, {2, 'a'}, {3, 'a'}, {4, 'b'}, {2, 'b'}, {3, 'b'} };
    std::vector<std::pair<int, char>> arr2 = { {4, 'a'}, {2, 'a'}, {3, 'a'}, {4, 'b'}, {2, 'b'}, {3, 'b'} };

    std::cout << "Merge Sort" << std::endl;
    MergeSort(arr1, 0, arr1.size() - 1);

    for(const auto& elem : arr1) {
        std::cout << "{ " << elem.first << "," << elem.second << " }";
    }

    std::cout << "\nQuick Sort" << std::endl;   
    quickSort(arr2, 0, arr2.size() - 1);

    for(const auto& elem : arr2) {
        std::cout << "{ " << elem.first << "," << elem.second << " }";
    }

    return 0;
}
