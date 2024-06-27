#include <stdio.h>

void TestN(int _n, int* _pN) {
	printf("[TestN] %d\t %d\n", _n, *(_pN));

	_n++; (*_pN)++;
}

void TestP(int* _p, int** _pP) {
	printf("[TestP] %d\t %d\n", *(_p), **(_pP));

	(*_p)++; (**_pP)++;
}

void TestNew(int*& _p, int**& _pp, int& _r) {
	_p = new int(2002);

	_pp = &_p;
	_r = *_p;
}

int main() {
	int n = 2021;
	TestN(n, &n);

	printf("* n is %d\n", n);

	int* pN = &n;
	TestP(pN, &pN);

	printf("** n is %d\n", n);

	// 수정된 코드
	int* p = nullptr;
	int** pp = nullptr;
	int m = 2022;

	TestNew(p, pp, m);

	if(p != nullptr) printf("*p is %d\n", *p);
	if(pp != nullptr) printf("**pp is %d\n", **pp);

	printf("m is %d\n", m);

	// 동적 메모리 해제
	delete p;

	return 0;
}
