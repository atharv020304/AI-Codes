#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

class Graph {
public:
    unordered_map<int, vector<int>> adj;

    void addEdge(int u, int v, bool directed = false) {
        adj[u].push_back(v);
        if (!directed) {
            adj[v].push_back(u);
        }
    }

    void bfs(int start, int n) {
        vector<bool> visited(n + 1, false);
        queue<int> q;

        q.push(start);
        visited[start] = true;

        cout << "BFS: ";
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            cout << node << " ";

            for (int neighbor : adj[node]) {
                if (!visited[neighbor]) {
                    q.push(neighbor);
                    visited[neighbor] = true;
                }
            }
        }
        cout << endl;
    }

    void dfs(int start, int n) {
        vector<bool> visited(n + 1, false);
        stack<int> s;

        s.push(start);
        visited[start] = true;

        cout << "DFS: ";
        while (!s.empty()) {
            int node = s.top();
            s.pop();
            cout << node << " ";

            // reverse dfs
            // for (auto it = adj[node].rbegin(); it != adj[node].rend(); ++it) {
            //     if (!visited[*it]) {
            //         s.push(*it);
            //         visited[*it] = true;
            //     }
            // }
            
            for(auto neighbour : adj[node]){
                if(!visited[neighbour]){
                    s.push(neighbour);
                    visited[neighbour] = true;
                }
            }
        }
        cout << endl;
    }
};

int main() {
    Graph g;

    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 4);
    g.addEdge(2, 5);
    g.addEdge(3, 6);
    g.addEdge(3, 7);

    int totalNodes = 7;

    g.bfs(1, totalNodes);
    g.dfs(1, totalNodes);

    return 0;
}
