#include <iostream>
#include <vector>
#include <stack>

using namespace std;

void DFS(int start, )

int main() {
	vector<vector<int>> adj_matrix = {
		{0, 1, 1, 0},
		{1, 0, 1, 1},
		{1, 1, 0, 0},
		{0, 1, 0, 0}
	};

	cout << "DFS: ";
	DFS(0, adj_matrix);
	cout << endl;

	return 0;
}