#pragma once



enum Grade {
	S,
	A,
	B,
	C,
	D
};

class Item { 
public:
	Item(int _index, const char* _name, int _level, Grade _grade);
	Item();
	~Item();
	Grade GetGrade() { return grade; };
	void SetGrade(Grade _grade);
	char* GetName() { return name; }
	char GetGradeInChar();
	void GradeUp();
	void Show();
	
private:
	int index;
	char* name;
	int level;
	Grade grade;

	static int startIndex;
	static int endIndex;
};

