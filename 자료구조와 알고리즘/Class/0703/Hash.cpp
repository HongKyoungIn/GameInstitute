#include <iostream>
#include <vector>

using namespace std;

class HashSet {
public:
	HashSet(int n) : m_size(n), m_data(m_size, -1) { }

	int Hash(int key) {
		return key % m_size;
	}

	void Insert(int value) {
		m_data[Hash(value)] = value;
	}

	bool Find(int value) {
		return (m_data[Hash(value)] == value);
	}

	void Erase(int value) {
		m_data[Hash(value)] = -1;
	}

private:
	int m_size;
	std::vector<int> m_data;
};

int main() {
	HashSet num_set(10);

	num_set.Insert(10);
	num_set.Insert(20);

	int number = 10;

	if(num_set.Find(number)) {
		cout << number << "is Found" << endl;
	}
	else {
		cout << number << "is Not Found" << endl;
	}

	number = 20;

	if(num_set.Find(number)) {
		cout << number << "is Found" << endl;
	}
	else {
		cout << number << "is Not Found" << endl;
	}

	return 0;
}

