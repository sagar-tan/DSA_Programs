#include <iostream>
#include <vector>
using namespace std;

// Build adjacency list from edge list
vector<vector<int>> buildAdjList(int v, vector<vector<int>> &edges) {
    vector<vector<int>> adj(v);
    for (int i = 0; i < edges.size(); i++) {
        int from = edges[i][0];
        int to = edges[i][1];
        adj[from].push_back(to);
    }
    return adj;
}

// Display adjacency list
void displayGraph(int v, vector<vector<int>> &adj) {
    for (int i = 0; i < adj.size(); i++) {
        cout << "Node " << i << ": ";
        for (int j = 0; j < adj[i].size(); j++) {
            cout << adj[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int v, e;
    cout << "No. of Vertices: ";
    cin >> v;
    cout << "No. of Edges: ";
    cin >> e;

    vector<vector<int>> edges;
    for (int i = 0; i < e; i++) {
        int from, to;
        cout << "Enter from: ";
        cin >> from;
        cout << "Enter to: ";
        cin >> to;
        edges.push_back(vector<int>{from, to});
    }

    vector<vector<int>> adj = buildAdjList(v, edges);
    displayGraph(v, adj);

    return 0;
}