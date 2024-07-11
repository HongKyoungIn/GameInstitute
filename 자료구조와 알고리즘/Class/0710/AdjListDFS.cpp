#include <iostream>
#include <vector>
#include <stack>

using namespace std;

void DFS(int start, vector<vector<int>>& adj_list) {
    int V = adj_list.size();
    vector<bool> visited(V, false);
    stack<int> s;
    s.push(start);
}

int main() {
    vector<vector<int>> adj_list =
    {
        {0, 1, 2},
        {1, 0, 2, 3},
        {2, 0, 1},
        {3, 1}
    };

    cout << "DFS: ";
    DFS(0, adj_list);
    cout << endl;

	return 0;
}