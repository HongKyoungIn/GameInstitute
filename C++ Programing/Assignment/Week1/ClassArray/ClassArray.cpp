#include <iostream>
#include "Item.h"
#include "ItemManager.h"

using namespace std;

int main() {
	int a, b;
	bool isComposition = false;

	ItemManager::GetInstance()->ItemAdd(1, "ghdruddls", 29, S);
	ItemManager::GetInstance()->ItemAdd(2, "dlghdud", 27, A);
	ItemManager::GetInstance()->ItemAdd(3, "chlwldnjs", 27, A);
	ItemManager::GetInstance()->ItemAdd(4, "rlarkdkms", 23, D);
	ItemManager::GetInstance()->ItemAdd(5, "rlatndls", 23, D);

	cout << "�ռ� �� ������ ���" << endl;
	ItemManager::GetInstance()->ShowItems();

	cout << endl;

	while(true) {
		if(isComposition) {
			break;
		}
		cout << "�ռ� �� �������� �Է� �Ͻÿ�. " << endl;
		cout << "�ռ� ���1 : ";
		cin >> a;

		cout << "�ռ� ���2 : ";
		cin >> b;
		isComposition = ItemManager::GetInstance()->ItemComposition(a, b);
		ItemManager::GetInstance()->ShowItems();
		
	}

	//ItemManager::GetInstance()->ItemComposition(1, 2);
	//cout << "�ռ� �� ������ ���" << endl;
	//ItemManager::GetInstance()->ShowItems();

	//cout << endl;

	//ItemManager::GetInstance()->ItemComposition(2, 4);
	//cout << "�ռ� �� ������ ���" << endl;
	//ItemManager::GetInstance()->ShowItems();

	//cout << endl;

	//ItemManager::GetInstance()->ItemComposition(2, 3);
	//cout << "�ռ� �� ������ ���" << endl;
	//ItemManager::GetInstance()->ShowItems();


	return 0;
}

