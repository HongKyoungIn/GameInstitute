#include <iostream>
#include <math.h>

using namespace std;

#define TARGETNUM 1000 // �������� �Ǵ� ��

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

	cout << "[�ݺ����� Ȱ���� ���]" << endl;
	cout << "1000 ���� ū ù ��° �Ҽ��� " << n << "�Դϴ�." << endl;

	cout << "[����Լ��� Ȱ���� ���]" << endl;
	cout << "1000 ���� ū ù ��° �Ҽ��� " << FindPrimeNumber(TARGETNUM) << "�Դϴ�." << endl;

	return 0;
}