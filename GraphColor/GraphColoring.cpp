// #include <iostream>
// #include <vector>

// using namespace std;

// struct Graph
// {
//     int V;
//     vector<vector<int>> adj;
//     vector<int> color;
// };

// Graph createGraph(int V)
// {
//     Graph g;
//     g.V = V;
//     g.adj.resize(V);
//     g.color.resize(V, 0);
//     return g;
// }

// void addEdge(Graph &g, int u, int v)
// {
//     g.adj[u].push_back(v);
//     g.adj[v].push_back(u);
// }

// bool isSafe(Graph &g, int v, int c)
// {
//     for (int neighbor : g.adj[v])
//     {
//         if (g.color[neighbor] == c)
//             return false;
//     }
//     return true;
// }

// bool solve(Graph &g, int v, int m)
// {
//     if (v == g.V)
//         return true;

//     for (int c = 1; c <= m; c++)
//     {
//         if (isSafe(g, v, c))
//         {
//             g.color[v] = c;
//             if (solve(g, v + 1, m))
//                 return true;
//             g.color[v] = 0;
//         }
//     }
//     return false;
// }

// void graphColoring(Graph &g, int m)
// {
//     if (solve(g, 0, m))
//     {
//         cout << "Colored: ";
//         for (int c : g.color)
//             cout << c << " ";
//         cout << endl;
//     }
//     else
//     {
//         cout << "No solution exists.\n";
//     }
// }

// int main()
// {
//     int V = 4;
//     Graph g = createGraph(V);

//     addEdge(g, 0, 1);
//     addEdge(g, 0, 2);
//     addEdge(g, 1, 2);
//     addEdge(g, 1, 3);

//     int m = 3;
//     graphColoring(g, m);

//     return 0;
// }

#include <iostream>
#include <bits/stdc++.h>

using namespace std;

bool isSafe(vector<vector<int>> G, int v, int c, int n, vector<int> &colorsA)
{
    for (int i = 0; i < n; i++)
    {
        if (G[v][i] == 1 && colorsA[i] == c)
        {
            return false;
        }
    }

    return true;
}

bool solve(int n, int m, int v, vector<vector<int>> G, vector<int> &colorsA)
{
    if (v == n)
    {
        return true;
    }

    for (int i = 1; i <= m; i++)
    {
        if (isSafe(G, v, i, n, colorsA))
        {
            colorsA[v] = i;
            if (solve(n, m, v + 1, G, colorsA))
            {
                return true;
            }
            colorsA[v] = -1;
        }
    }

    return true;
}

void GC(int m, int n, int e, vector<vector<int>> G)
{
    vector<int> colorsA(n, -1);
    if (solve(n, m, 0, G, colorsA))
    {
        cout << "Answer : ";
        for (int i : colorsA)
        {
            cout << i << " ";
        }
        cout << endl;
    }
    else
    {
        cout << "Not Possible\n";
    }
}

int main()
{
    int n, e;

    cout << "Enter number of node in graph : ";
    cin >> n;
    cout << "Enter number of edges in graph : ";
    cin >> e;

    // int G[n][n];
    vector<vector<int>> G(n, vector<int>(n, 0));

    for (int i = 0; i < e; i++)
    {
        int a, b;
        cout << "Enter edge : ";
        cin >> a >> b;
        G[a][b] = G[b][a] = 1;
    }

    int m;
    cout << "Enter number of colors : ";
    cin >> m;

    GC(m, n, e, G);
}
