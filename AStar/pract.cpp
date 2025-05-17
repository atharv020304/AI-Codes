#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
#include <set>
#include <climits>
using namespace std;

class Graph{
    public:
        char Data;
        int h_value;
        vector<pair<Graph*,int>> adj;

        Graph(char Data, int _h_v){
            this->Data = Data;
            this->h_value = _h_v;
        }
        void AddEdge(Graph* neighbor, int weight) {
        adj.push_back({neighbor, weight});
         }
};


pair<int,vector<char>> findAstar(unordered_map<char,Graph*>& graphMap,int start,int goal){
priority_queue<pair<int,Graph*>, vector<pair<int,Graph*>> ,greater<>> pq;
unordered_map<char,int> gCost;
unordered_map<char,char> parent;

for(auto it = graphMap.begin(); it != graphMap.end(); it++){
    char ch = it->first;
    gCost[ch] = INT_MAX;
}

gCost[start] = 0;

pq.push({gCost[start]+graphMap[start]->h_value,graphMap[start]});

while(!pq.empty()){
    pair<int,Graph*> tp = pq.top();
    pq.pop();
    Graph* current = tp.second;
    if(current->Data == goal) break;

    for(int i = 0 ; i < current->adj.size(); i++){
        Graph* neigh = current->adj[i].first;
        int wt = current->adj[i].second;

        int tentative_g = gCost[current->Data] + wt;
        if(tentative_g < gCost[neigh->Data]){
            gCost[neigh->Data] = tentative_g;
            parent[neigh->Data] = current->Data;
            int f_cost = tentative_g + neigh->h_value;
            pq.push({f_cost,neigh});

        }
    }
}

vector<char> path;
for(char at = goal ;at != start ; at = parent[at])
    path.push_back(at);
path.push_back(start);
std::reverse(path.begin(),path.end());

    return {gCost[goal],path};
}


int main() {
    unordered_map<char,Graph*> graphMap;
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


    pair<int, vector<char>> result = findAstar(graphMap, 'A', 'G');

    cout << "Path: ";
    for (char node : result.second) cout << node << " ";
    cout << "\nCost: " << result.first << endl;

    

    return 0;
}