#pragma once
#include "Item.h"

class ItemManager { 
public:
	static ItemManager* GetInstance() {
		static ItemManager itemManager;
		return &itemManager;
	}

	bool ItemComposition(int a, int b);
	
	void ItemAdd(int index, const char* name, int level, Grade grade);

	void ShowItems();
private:
	ItemManager() = default;
	~ItemManager();
	Item* ItemList[10];
	int currentIndex = 0;
};

