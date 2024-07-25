#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    vector<int> v = { 1, 1, 2, 3, 3, 4, 5, 1, 1, 6 };

    cout << "Á¤·Ä sort(v.begin(), v.end());\n";
    sort(v.begin(), v.end());
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << "\t";
    }

    cout << "\n\n";

    cout << "º¤ÅÍ.erase(unique(v.begin(), v.end()), v.end())\n";
    v.erase(unique(v.begin(), v.end()), v.end());
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << "\t";
    }

    cout << "\n\n";

    return 0;
}
