#include <iostream>

using namespace std;

class Int {
	int num = 0;

	struct Int_op {
		void add(Int& a) { a.num++; }
		void sub(Int& a) { a.num--; }
	};

	struct Int_ui {
		void show(const Int& a) { cout << a.num << endl; }
	};

public:
	void Add() {
		Int_op a;
		a.add(*this);
	}
	
	void Show() {
		Int_ui a;
		a.show(*this);
	}

};

int main() {

	return 0;
}

