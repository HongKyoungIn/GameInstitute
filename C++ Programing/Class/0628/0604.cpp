#include <iostream>

using namespace std;

class Player {
	int id = 0;

public:
	virtual void Move() {
		cout << "Player" << endl;
	}
};

class Hero : public Player {
public:
	void Move() {
		cout << "Hero" << endl;
	}
};

class Enemy : public Player {
	void Move() {
		cout << "Enemy" << endl;
	}
};

class Boss : public Player {
	void Move() {
		cout << "Boss" << endl;
	}
};

class PlayerManager {

};

int main() {
	Player playerList[] = { Hero(), Enemy(), Boss() };

	for(size_t i = 0; i < 3; i++) {
		playerList[i].Move();
	}

	return 0;
}

