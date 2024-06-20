#include <iostream>

using namespace std;

class PrintAddNumber {
public:
	void operator()(int a, int b) { std::cout << a + b << std::endl; }
};

int main() {
	PrintAddNumber print_add_number;
	print_add_number(3, 5);

	// PrintAddNumber()(3, 5);
}