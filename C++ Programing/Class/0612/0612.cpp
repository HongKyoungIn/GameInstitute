#include <iostream>

using namespace std;

class Test {
	int n1 = 1;

public:
	void Func() {
		n1 = 0;
	}

	void Show() {
		cout << n1 << endl;
	}

	friend Test AddTest(Test t1, Test t2);
};

Test AddTest(Test t1, Test t2) {
	Test t;
	t.n1 = t1.n1 + t2.n1;

	return t;
}

int main() {
	Test t1;
	Test t2;

	Test add = AddTest(t1, t2);

	add.Show();

	return 0;
}

