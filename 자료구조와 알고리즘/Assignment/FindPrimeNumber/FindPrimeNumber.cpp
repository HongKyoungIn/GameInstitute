#include <iostream>
#include <math.h>

using namespace std;

#define TARGETNUM 1000 // 기준점이 되는 수

bool IsPrimeNumber(int n, int divide = 2) {
	if(n % divide == 0) {
		return false;
	}
	else if(divide * divide > n) {
		return true;
	}
	else {
		IsPrimeNumber(n, ++divide);
	}
}

int FindPrimeNumber(int n) {
	if(IsPrimeNumber(n + 1)) {
		return n + 1;
	}
	else {
		FindPrimeNumber(n + 1);
	}
}

int main() {
	int n = TARGETNUM;

	while(true) {
		bool prime = true;
		int max = sqrt(n);
		for(size_t i = 2; i < max; i++) {
			if(n % i == 0) {
				prime = false;
				break;
			}
		}

		if(n > TARGETNUM && prime == true) {
			break;
		}
		else {
			n++;
		}
	}

	cout << "[반복문을 활용한 방법]" << endl;
	cout << "1000 보다 큰 첫 번째 소수는 " << n << "입니다." << endl;

	cout << "[재귀함수를 활용한 방법]" << endl;
	cout << "1000 보다 큰 첫 번째 소수는 " << FindPrimeNumber(TARGETNUM) << "입니다." << endl;

	return 0;
}