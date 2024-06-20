// n��° ������ ��ǥ �������� ������
// n-1��° ���� ������ ������������ ������.

#include <iostream>

using namespace std;

int MoveNum = 0;

void Move(int _num, char _start, char _end) {
	printf("%d ������ %c���� %c�� �ű�ϴ�.\n", _num, _start, _end);
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

	cout << "������ ������ �Է��Ͻÿ� : ";
	cin >> num;

	Hanoi(num, 'A', 'C', 'B');
	cout << "�̵� Ƚ�� : " << MoveNum << endl;

	return 0;
}