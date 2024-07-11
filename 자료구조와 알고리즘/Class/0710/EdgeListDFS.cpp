#include <iostream>
#include <vector>
#include <stack>

using namespace std;

void DFS(int start, const vector<pair<int, int>>& edges, int V) {
    vector<bool> visited(V, false);
    stack<int> s;
    s.push(start);

    while(!s.empty()) {
        int node = s.top();
        s.pop();

        if(!visited[node]) {
            cout << node << " ";
            visited[node] = true;
        }

        for(const auto& edge : edges) {
            if(edge.first == node && !visited[edge.second]) {
                s.push(edge.second);
            }
        }
    }
}

int main() {
    vector<pair<int, int>> edges = {
        {0, 1},
        {0, 2},
        {1, 2},
        {1, 3}
    };

    cout << "DFS: ";
    DFS(0, edges, edges.size());
    cout << endl;

    return 0;
}