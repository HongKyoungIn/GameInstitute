// n번째 원반을 목표 지점으로 보낸다
// n-1번째 까지 원반은 경유지점으로 보낸다.

#include <iostream>

using namespace std;

int MoveNum = 0;

void Move(int _num, char _start, char _end) {
	printf("%d 원반을 %c에서 %c로 옮깁니다.\n", _num, _start, _end);
	MoveNum++;
}

void Hanoi(int _num, char _start, char _end, char _temp) {
	if(_num == 1) {
		Move(_num, _start, _end);
	}
	else {
		Hanoi(_num - 1, _start, _temp, _end);
		Move(_num, _start, _end);
		Hanoi(_num - 1, _temp, _end, _start);
	}
}

int main() {
	int num = 0;

	cout << "원반의 갯수를 입력하시오 : ";
	cin >> num;

	Hanoi(num, 'A', 'C', 'B');
	cout << "이동 횟수 : " << MoveNum << endl;

	return 0;
}