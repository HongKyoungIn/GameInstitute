#include <iostream>

using namespace std;

class Test {
	int num = 1;

public:
	Test() { }
	Test(int a) : num(a) { }

	void Show() {
		cout << num << endl;
	}

	friend Test AddOnePrefix(Test& x);

	friend Test AddOnePostfix(Test& x);
};

Test AddOnePrefix(Test& x) {
	x.num++;
	return x;
}

Test AddOnePostfix(Test& x) {
	Test temp = x;
	x.num++;
	return temp;
}

int main() {
	Test a(10);
	Test b = AddOnePrefix(a);
	b.Show();
	Test c = AddOnePostfix(a);
	c.Show();
	a.Show();

	return 0;
}

