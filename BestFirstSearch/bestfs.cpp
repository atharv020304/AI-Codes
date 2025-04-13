#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>

using namespace std;


class Graph {
public:
    char Data;
    int heuristic_value;
    vector<Graph*> adj;

    Graph(char data, int hval) {
        Data = data;
        heuristic_value = hval;
    }

    void AddEdge(Graph* neighbor) {
        adj.push_back(neighbor);
    }
};


struct MinHeuristic {
    bool operator()(Graph* a, Graph* b) {
        return a->heuristic_value > b->heuristic_value;
    }
};


vector<char> BestFirstSearch(unordered_map<char, Graph*>& graphMap, char start, char goal) {
    priority_queue<Graph*, vector<Graph*>, MinHeuristic> minHeap;
    unordered_map<char, bool> visited;
    unordered_map<char, char> parentMap;
    vector<pair<char, char>> closed;
    vector<char> path;

    visited[start] = true;
    minHeap.push(graphMap[start]);
    parentMap[start] = '-';  

    while (!minHeap.empty()) {
        Graph* current = minHeap.top();
        minHeap.pop();

        char currNode = current->Data;
        closed.push_back({ currNode, parentMap[currNode] });

        if (currNode == goal) break;

        for (auto& neighbor : current->adj) {
            if (!visited[neighbor->Data]) {
                visited[neighbor->Data] = true;
                parentMap[neighbor->Data] = currNode;
                minHeap.push(neighbor);
            }
        }
    }


    char current = goal;
    while (current != '-') {
        path.push_back(current);
        current = parentMap[current];
    }
    reverse(path.begin(), path.end());

    return path;
}


int main() {
    unordered_map<char, Graph*> graphMap;

    
    graphMap['S'] = new Graph('S', 10);
    graphMap['A'] = new Graph('A', 9);
    graphMap['B'] = new Graph('B', 7);
    graphMap['C'] = new Graph('C', 8);
    graphMap['D'] = new Graph('D', 8);
    graphMap['H'] = new Graph('H', 6);
    graphMap['F'] = new Graph('F', 6);
    graphMap['G'] = new Graph('G', 3);
    graphMap['E'] = new Graph('E', 0);

    
    graphMap['S']->AddEdge(graphMap['A']);
    graphMap['S']->AddEdge(graphMap['B']);
    graphMap['A']->AddEdge(graphMap['C']);
    graphMap['B']->AddEdge(graphMap['D']);
    graphMap['B']->AddEdge(graphMap['H']);
    graphMap['H']->AddEdge(graphMap['F']);
    graphMap['H']->AddEdge(graphMap['G']);
    graphMap['G']->AddEdge(graphMap['E']);

    vector<char> path = BestFirstSearch(graphMap, 'S', 'E');

    cout << "Best First Search Path from S to E:\n";
    for (char node : path) {
        cout << node << " ";
    }
    cout << "\n";

    return 0;
}
