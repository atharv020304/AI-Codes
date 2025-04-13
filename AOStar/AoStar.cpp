#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
using namespace std;

class Graph {
public:
    char Data;
    int heuristic_value;
    vector<vector<pair<Graph*, int> > > adj; 
    bool solved;

    Graph(char data, int hval) {
        Data = data;
        heuristic_value = hval;
        solved = false;
    }

    void AddOrEdge(const vector<pair<Graph*, int> >& group) {
        adj.push_back(group); 
    }
};


void AOStar(Graph* node, unordered_map<char, bool>& visited) {
    if (node->solved || visited[node->Data])
        return;

    visited[node->Data] = true;

    int min_cost = INT_MAX;
    vector<pair<Graph*, int> > best_group;

   
    for (size_t i = 0; i < node->adj.size(); ++i) {
        int group_cost = 0;
        vector<pair<Graph*, int> >& group = node->adj[i];

        for (size_t j = 0; j < group.size(); ++j) {
            Graph* child = group[j].first;
            int weight = group[j].second;
            group_cost += weight + child->heuristic_value;
        }

        if (group_cost < min_cost) {
            min_cost = group_cost;
            best_group = group;
        }
    }

    if (!best_group.empty())
        node->heuristic_value = min_cost;

    
    for (size_t i = 0; i < best_group.size(); ++i) {
        AOStar(best_group[i].first, visited);
    }

   
    bool allSolved = true;
    for (size_t i = 0; i < best_group.size(); ++i) {
        if (!best_group[i].first->solved) {
            allSolved = false;
            break;
        }
    }

    if (allSolved) node->solved = true;
}


void printSolution(Graph* start) {
    cout << start->Data;

    if (start->adj.empty()) return;

    int min_cost = INT_MAX;
    vector<pair<Graph*, int> > best_group;

    
    for (size_t i = 0; i < start->adj.size(); ++i) {
        int group_cost = 0;
        vector<pair<Graph*, int> >& group = start->adj[i];

        for (size_t j = 0; j < group.size(); ++j) {
            group_cost += group[j].second + group[j].first->heuristic_value;
        }

        if (group_cost < min_cost) {
            min_cost = group_cost;
            best_group = group;
        }
    }

    
    for (size_t i = 0; i < best_group.size(); ++i) {
        cout << " --" << best_group[i].second << "--> ";
        printSolution(best_group[i].first);
    }
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

    
    graphMap['A']->AddOrEdge(vector<pair<Graph*, int> >(1, make_pair(graphMap['B'], 1)));
    graphMap['A']->AddOrEdge(vector<pair<Graph*, int> >(1, make_pair(graphMap['C'], 4)));

    graphMap['B']->AddOrEdge(vector<pair<Graph*, int> >(1, make_pair(graphMap['C'], 2)));
    graphMap['B']->AddOrEdge(vector<pair<Graph*, int> >(1, make_pair(graphMap['D'], 3)));

    graphMap['C']->AddOrEdge(vector<pair<Graph*, int> >(1, make_pair(graphMap['E'], 5)));

    vector<pair<Graph*, int> > andGroupD;
    andGroupD.push_back(make_pair(graphMap['F'], 2));
    andGroupD.push_back(make_pair(graphMap['G'], 4));
    graphMap['D']->AddOrEdge(andGroupD);

    graphMap['E']->AddOrEdge(vector<pair<Graph*, int> >(1, make_pair(graphMap['G'], 3)));
    graphMap['F']->AddOrEdge(vector<pair<Graph*, int> >(1, make_pair(graphMap['G'], 1)));

    unordered_map<char, bool> visited;
    AOStar(graphMap['A'], visited);

    cout << "\nFinal Heuristic Value of A: " << graphMap['A']->heuristic_value << endl;
    cout << "Final Solution Subgraph: ";
    printSolution(graphMap['A']);
    cout << endl;

    return 0;
}
