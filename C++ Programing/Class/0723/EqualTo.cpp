#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>

using namespace std;

std::function<void(int)> Func(std::function<void(int)> fn) {
    return fn;
}

bool foo1(int a) { return true; }
bool foo2(int a, int b) {  }
string foo3(float a, double b) {  }
void foo4() {  }


int main() {
    equal_to<int> comp;
    cout << comp(7, 3) << endl;

    Equal<int> com;
    cout << com(7, 7) << endl;

    return 0;
}
