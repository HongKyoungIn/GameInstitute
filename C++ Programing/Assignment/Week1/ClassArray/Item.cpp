#include "Item.h"
#include "cstring"
#include <iostream>

using namespace std;

int Item::endIndex = 0;

Item::Item(int _index, const char* _name, int _level, Grade _grade) {
	index = _index;

	int len = strlen(_name) + 1;
    name = new char[len];
	strcpy_s(name, len, _name);

	level = _level;

	grade = _grade;
    endIndex++;
}

Item::Item() {
	index = 0;
	name = NULL;
	level = 0;
	grade = D;
}

Item::~Item() { 
	delete[] name;
}

void Item::SetGrade(Grade _grade) {
	grade = _grade;
}

char Item::GetGradeInChar() {
    switch(grade) {
    case S: 
        return 'S';
    case A: 
        return 'A';
    case B: 
        return 'B';
    case C: 
        return 'C';
    case D: 
        return 'D';
    default: 
        return 'F';
    }
}

void Item::GradeUp() { 
    switch(grade) {
    case D:
        grade = C;
        break;
    case C:
        grade = B;
        break;
    case B:
        grade = A;
        break;
    case A:
        grade = S;
        break;
    case S:
        std::cout << "Grade is already at the highest level (S)." << std::endl;
        break;
    default:
        std::cout << "Unknown grade." << std::endl;
        break;
    }
	cout << grade << endl;
}

void Item::Show() { 
	cout << index << ", " << name << ", " << level << ", " << "'" << GetGradeInChar() << "'" << endl;
}