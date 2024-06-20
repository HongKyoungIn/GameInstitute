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

	cout << "합성 전 아이템 목록" << endl;
	ItemManager::GetInstance()->ShowItems();

	cout << endl;

	while(true) {
		if(isComposition) {
			break;
		}
		cout << "합성 할 아이템을 입력 하시오. " << endl;
		cout << "합성 재료1 : ";
		cin >> a;

		cout << "합성 재료2 : ";
		cin >> b;
		isComposition = ItemManager::GetInstance()->ItemComposition(a, b);
		ItemManager::GetInstance()->ShowItems();
		
	}

	//ItemManager::GetInstance()->ItemComposition(1, 2);
	//cout << "합성 후 아이템 목록" << endl;
	//ItemManager::GetInstance()->ShowItems();

	//cout << endl;

	//ItemManager::GetInstance()->ItemComposition(2, 4);
	//cout << "합성 후 아이템 목록" << endl;
	//ItemManager::GetInstance()->ShowItems();

	//cout << endl;

	//ItemManager::GetInstance()->ItemComposition(2, 3);
	//cout << "합성 후 아이템 목록" << endl;
	//ItemManager::GetInstance()->ShowItems();


	return 0;
}

