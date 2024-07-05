#include <iostream>

using namespace std;

template <class T>
class MyClass {
public:
	MyClass(T v) : num(v) { }
	~MyClass() { }

	void Set(T arg) {
		num = arg;
	}

	int Get() {
		return num;
	}

private:
	T num;
};

int main() {
    MyClass<int> a;
    a.Set(1);
    cout << a.Get() << endl;

    MyClass<float> b;

    return 0;
}