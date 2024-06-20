#include <iostream>

using namespace std;

class MyArray {
	int* p = nullptr;
	int size = 0;

public:
	MyArray(int size) : size(size) {
		p = new int[size];
	}
	~MyArray() {
		delete[] p;
	}

	void Set(int index, int n) {
		p[index] = n;
	}

	int Get(int index) {
		return p[index];
	}

	int& operator[](int index) { 
		return p[index];
	}

	/*int operator[](int index) const {
		return p[index];
	}*/
};

int main() {
	MyArray myArr(3);

	myArr[0] = 1;
	int n = myArr[0];
	cout << n << endl;

	myArr.Set(0, 1);
	myArr.Set(1, 2);

	n = myArr.Get(1);

	cout << n << endl;

	cout << myArr[0] << endl;

	return 0;
}