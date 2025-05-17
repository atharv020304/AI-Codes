#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

bool isColorValid(unordered_map<int,vector<int>>& graph, int currNode, int color, vector<int>& colorsArray) {
    for (auto neighbor : graph[currNode]) {
        if (colorsArray[neighbor] == color) return false;
    }
    return true;
}

bool assignColors(unordered_map<int,vector<int>>& graph, int totalNodes, int maxColors, vector<int>& colorsArray, int currNode) {
    if (currNode == totalNodes) return true;

    for (int color = 0; color < maxColors; color++) {
        if (isColorValid(graph, currNode, color, colorsArray)) {
            colorsArray[currNode] = color;
            if (assignColors(graph, totalNodes, maxColors, colorsArray, currNode + 1))
                return true;
            colorsArray[currNode] = -1; 
        }
    }
    return false;
}

void graphColoring(unordered_map<int,vector<int>>& graph, int totalNodes, int maxColors) {
    vector<int> colorsArray(totalNodes, -1);

    if (assignColors(graph, totalNodes, maxColors, colorsArray, 0)) {
        cout << "Color Assignment: ";
        for (int color : colorsArray) cout << color << " ";
        cout << endl;
    } else {
        cout << "Not possible to color with " << maxColors << " colors." << endl;
    }
}

int main() {
    unordered_map<int, vector<int>> graph;
    int maxColors = 3;
    int totalNodes = 7; 

    graph[0].push_back(1); graph[1].push_back(0);
    graph[0].push_back(2); graph[2].push_back(0);
    graph[0].push_back(3); graph[3].push_back(0);
    graph[2].push_back(4); graph[4].push_back(2);
    graph[2].push_back(3); graph[3].push_back(2);
    graph[1].push_back(2); graph[2].push_back(1);
    graph[3].push_back(5); graph[5].push_back(3);

   
    for (int i = 0; i < totalNodes; i++) {
        if (graph.find(i) == graph.end()) graph[i] = {};
    }

    graphColoring(graph, totalNodes, maxColors);
    return 0;
}
