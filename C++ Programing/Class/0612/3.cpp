#include <iostream>

using namespace std;

class Test {
private:
	int num = 1;

public:
	int Get() { return num; }
	void Set(int a) { num = a; }

	Test Sum1(Test obj) {
		Test temp;
		temp.num += obj.num;
		return temp;
	}

	friend Test Sum2(Test t1, Test t2);
};

Test Sum2(Test t1, Test t2) {
	Test temp;
	temp.num = t1.Get() + t2.Get();
	return temp;
}

int main() {
	Test x;
	x.Set(1);

	Test y;
	y.Set(2);

	Test z1 = x.Sum1(y);
	Test z2 = Sum2(x, y);

	cout << z1.Get() << " " << z2.Get();

	return 0;
}

