#include "ItemManager.h"
#include <iostream>

bool ItemManager::ItemComposition(int a, int b) {
    std::cout << std::endl;
    if(ItemList[a - 1]->GetGrade() == ItemList[b - 1]->GetGrade()) {
        std::cout << "합성 후 아이템 목록" << std::endl;
        switch(ItemList[a - 1]->GetGrade()) {
        case D:
            ItemList[a - 1]->SetGrade(C);
            ItemAdd(currentIndex + 1, ItemList[a - 1]->GetName(), 1, ItemList[a - 1]->GetGrade());
            delete ItemList[a - 1];
            delete ItemList[b - 1];
            ItemList[a - 1] = nullptr;
            ItemList[b - 1] = nullptr;
            break;
        case C:
            ItemList[a - 1]->SetGrade(B);
            ItemAdd(currentIndex + 1, ItemList[a - 1]->GetName(), 1, ItemList[a - 1]->GetGrade());
            delete ItemList[a - 1];
            delete ItemList[b - 1];
            ItemList[a - 1] = nullptr;
            ItemList[b - 1] = nullptr;
            break;
        case B:
            ItemList[a - 1]->SetGrade(A);
            ItemAdd(currentIndex + 1, ItemList[a - 1]->GetName(), 1, ItemList[a - 1]->GetGrade());
            delete ItemList[a - 1];
            delete ItemList[b - 1];
            ItemList[a - 1] = nullptr;
            ItemList[b - 1] = nullptr;
            break;
        case A:
            ItemList[a - 1]->SetGrade(S);
            ItemAdd(currentIndex + 1, ItemList[a - 1]->GetName(), 1, ItemList[a - 1]->GetGrade());
            delete ItemList[a - 1];
            delete ItemList[b - 1];
            ItemList[a - 1] = nullptr;
            ItemList[b - 1] = nullptr;
            break;
        case S:
            std::cout << "Grade is already at the highest level (S)." << std::endl;
            break;
        default:
            std::cout << "Unknown grade." << std::endl;
            break;
        }
        return true;
    }
    else if(ItemList[a - 1]->GetGrade() == S || ItemList[b - 1]->GetGrade() == S) {
        std::cout << "이미 등급이 S 등급 입니다." << std::endl;
        return false;
    }
    else {
        std::cout << "등급이 다릅니다." << std::endl;
        return false;
    }
   
}

void ItemManager::ItemAdd(int index, const char* name, int level, Grade grade) {
    ItemList[currentIndex] = new Item(index, name, level, grade);
    currentIndex++;
}

void ItemManager::ShowItems() { 
    for(size_t i = 0; i < 10; i++) {
        if(ItemList[i] != nullptr)
            ItemList[i]->Show();
    }
    std::cout << std::endl;
}

ItemManager::~ItemManager() { }