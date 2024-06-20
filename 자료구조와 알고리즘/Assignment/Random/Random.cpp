#include <iostream>
#include <vector>
#include <random>
#include <Windows.h>

using namespace std;

vector<char> ItemInfo = { 'A','B','C','D','E','F','G','H' };
vector<int> ItemProb = { 1,3,6,10,10,20,20,30 };
vector<int> AccumulatedProb;
vector<char> ItemIndexTable;

uniform_int_distribution<int> uniform_dist(0, 99); // 0���� 99���� �յ� ����
discrete_distribution<int> discreteDist({ 1, 3, 6, 10, 10, 20, 20, 30 }); // Ȯ���� ���

char PickItemByAccumulatedProb(mt19937& gen) {
	//���� Ȯ�� ���̺��� �̿��Ͽ� �������� �����ϵ��� �ۼ��� ������.
	return 'A';
};

char PickItemByIndexTable(mt19937& gen) {

	// O(1) �ð��� �������� ������ �����ϵ��� �ۼ��� ������.

	return 'A';
}

char GetItemByDiscreteDist(mt19937& gen) {
	// �̻� Ȯ�� ������ �̿��Ͽ� �������� �����ϵ��� �ۼ��� ������.
	return 'A';
}

// �׽�Ʈ �ڵ�
void Test(const int TEST_COUNT) {
	random_device rd;
	mt19937 gen(rd());

	char _temp;

	cout << "-------- PickItemByAccumulatedProb --------" << endl << endl;
	{
		int _test1[8] = { 0 };
		ULONGLONG startTick = GetTickCount64();

		for(int i = 0; i < TEST_COUNT; i++) {
			_temp = PickItemByAccumulatedProb(gen);
			_test1[_temp - 'A'] += 1;
		}
		ULONGLONG endTick = GetTickCount64();

		for(int i = 0; i < 8; i++)
			cout << (char)('A' + i) << " : " << (float)_test1[i] / (float)(TEST_COUNT / 100) << endl;

		cout << "<<<<<<  �׽�Ʈ ��� 1 :  " << (endTick - startTick) << endl;
	}

	cout << "-------- PickItemByIndexTable --------" << endl << endl;
	{
		int _test1[8] = { 0 };
		ULONGLONG startTick = GetTickCount64();
		for(int i = 0; i < TEST_COUNT; i++) {
			_temp = PickItemByIndexTable(gen);
			_test1[_temp - 'A'] += 1;
		}
		ULONGLONG endTick = GetTickCount64();

		for(int i = 0; i < 8; i++)
			cout << (char)('A' + i) << " : " << (float)_test1[i] / (float)(TEST_COUNT / 100) << endl;

		cout << "<<<<<<  �׽�Ʈ ��� 2 :  " << (endTick - startTick) << endl;
	}

	cout << "-------- GetItemByDiscreteDist --------" << endl << endl;
	{
		int _test1[8] = { 0 };
		ULONGLONG startTick = GetTickCount64();
		for(int i = 0; i < TEST_COUNT; i++) {
			_temp = GetItemByDiscreteDist(gen);
			_test1[_temp - 'A'] += 1;
		}
		ULONGLONG endTick = GetTickCount64();

		for(int i = 0; i < 8; i++)
			cout << (char)('A' + i) << " : " << (float)_test1[i] / (float)(TEST_COUNT / 100) << endl;

		cout << "<<<<<<  �׽�Ʈ ��� 3 :  " << (endTick - startTick) << endl;
	}
}

void main() {
	// 1. ����Ȯ�� ���̺� ������ ����

	// 2. �ε��� ���̺� ������ ����

	// 3. �׽�Ʈ!
	Test(1000000);
}