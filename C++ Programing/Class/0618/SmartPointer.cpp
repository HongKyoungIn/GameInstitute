// ������ �����ε� Ȱ�� 
//	* ������ ������ �����ε� // ��ü�� ������ ó�� �ٷ�� ���� ����.

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
