#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
#include <set>
#include <climits>
using namespace std;

class Graph {
public:
    char Data;
    int heuristic_value;
    vector<pair<Graph*, int>> adj;

    Graph(char data, int hval) {
        Data = data;
        heuristic_value = hval;
    }

    void AddEdge(Graph* neighbor, int weight) {
        adj.push_back({neighbor, weight});
    }
};

pair<vector<char>, int> findAstar(unordered_map<char, Graph*>& graphMap, char start, char goal) {
    priority_queue<pair<int, Graph*>, vector<pair<int, Graph*>>, greater<>> pq;
    unordered_map<char, int> gCost;
    unordered_map<char, char> parent;

    for (auto it = graphMap.begin(); it != graphMap.end(); ++it) {
        char ch = it->first;
        gCost[ch] = INT_MAX;
    }

    gCost[start] = 0;
    pq.push({gCost[start] + graphMap[start]->heuristic_value, graphMap[start]});

    while (!pq.empty()) {
        pair<int, Graph*> top = pq.top(); pq.pop();
        Graph* current = top.second;

        if (current->Data == goal) break;

        for (int i = 0; i < current->adj.size(); ++i) {
            Graph* neighbor = current->adj[i].first;
            int weight = current->adj[i].second;

            int tentative_g = gCost[current->Data] + weight;
            if (tentative_g < gCost[neighbor->Data]) {
                gCost[neighbor->Data] = tentative_g;
                parent[neighbor->Data] = current->Data;
                int f_cost = tentative_g + neighbor->heuristic_value;
                pq.push({f_cost, neighbor});
            }
        }
    }

    vector<char> path;
    for (char at = goal; at != start; at = parent[at])
        path.push_back(at);
    path.push_back(start);
    reverse(path.begin(), path.end());

    int final_cost = gCost[goal];
    return {path, final_cost};
}

int main() {
    unordered_map<char, Graph*> graphMap;
    graphMap['A'] = new Graph('A', 5);
    graphMap['B'] = new Graph('B', 6);
    graphMap['C'] = new Graph('C', 4);
    graphMap['D'] = new Graph('D', 3);
    graphMap['E'] = new Graph('E', 3);
    graphMap['F'] = new Graph('F', 1);
    graphMap['G'] = new Graph('G', 0);

    graphMap['A']->AddEdge(graphMap['B'], 1);
    graphMap['A']->AddEdge(graphMap['C'], 4);
    graphMap['B']->AddEdge(graphMap['C'], 2);
    graphMap['B']->AddEdge(graphMap['D'], 3);
    graphMap['C']->AddEdge(graphMap['E'], 5);
    graphMap['D']->AddEdge(graphMap['F'], 2);
    graphMap['D']->AddEdge(graphMap['G'], 4);
    graphMap['E']->AddEdge(graphMap['G'], 3);
    graphMap['F']->AddEdge(graphMap['G'], 1);

    // graphMap['S'] = new Graph('S',7);
    // graphMap['A'] = new Graph('A',6);
    // graphMap['B'] = new Graph('B',2);
    // graphMap['C'] = new Graph('C',1);
    // graphMap['D'] = new Graph('D',0);


    // graphMap['S']->AddEdge(graphMap['A'],1);
    // graphMap['S']->AddEdge(graphMap['B'],4);
    // graphMap['A']->AddEdge(graphMap['B'],2);
    // graphMap['A']->AddEdge(graphMap['C'],5);
    // graphMap['A']->AddEdge(graphMap['D'],12);
    // graphMap['B']->AddEdge(graphMap['C'],2);
    // graphMap['C']->AddEdge(graphMap['D'],3);



    // pair<vector<char>, int> result = findAstar(graphMap, 'S', 'D');

    pair<vector<char>, int> result = findAstar(graphMap, 'A', 'G');

    cout << "Path: ";
    for (char node : result.first) cout << node << " ";
    cout << "\nCost: " << result.second << endl;

    return 0;
}
