#include <iostream>

using namespace std;

class Out {
	class In {
		static int ivalue;
		void func1(int value);
	};

	void func2(int value);
};

int Out::In::ivalue = 0;

void Out::In::func1(int value) {

}

void Out::func2(int value) {

}


int main() {

	return 0;
}

