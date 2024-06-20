// 연산자 오버로딩 활용 
//	* 포인터 연산자 오버로딩 // 객체를 포인터 처럼 다루는 것이 가능.

#include <iostream>
using namespace std;

class Int {
	int data = 0;
	
public:
	Int(int n) : data(n) { }
	void Show() {
		cout << data << endl;
	}
};

class IntPtr {
	Int* ptr;

public:
	IntPtr(Int* p) : ptr(p) { }
	~IntPtr() { delete ptr; }

	void operator->(){ }
};

int main() {
	IntPtr ptr(new Int(2));

	ptr->Show();
	cout << *ptr << endl;

	return 0;
}
