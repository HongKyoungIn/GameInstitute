#include <iostream>
#include <vector>
#include <list>

using namespace std;

class HashSet {
public:
    HashSet(int n) : m_size(n), m_data(m_size) { }

    int Hash(int key) {
        return key % m_size;
    }

    void Insert(int value) {
        m_data[Hash(value)].push_back(value);
    }

    bool Find(int value) {
        auto it = std::find(m_data[Hash(value)].begin(), m_data[Hash(value)].end(), value);
        return (it != m_data[Hash(value)].end());
    }

    void Erase(int value) {
        m_data[Hash(value)].remove(value);
    }

private:
    int m_size;
    std::vector<std::list<int>> m_data;
};

int main() {
    HashSet num_set(10);

    num_set.Insert(10);
    num_set.Insert(20);

    int number = 10;

    if(num_set.Find(number)) {
        cout << number << " is Found" << endl;
    }
    else {
        cout << number << " is Not Found" << endl;
    }

    num_set.Erase(10);

    if(num_set.Find(number)) {
        cout << number << " is Found" << endl;
    }
    else {
        cout << number << " is Not Found" << endl;
    }

    number = 30;

    if(num_set.Find(number)) {
        cout << number << " is Found" << endl;
    }
    else {
        cout << number << " is Not Found" << endl;
    }

    num_set.Insert(30);

    if(num_set.Find(number)) {
        cout << number << " is Found" << endl;
    }
    else {
        cout << number << " is Not Found" << endl;
    }

    return 0;
}
