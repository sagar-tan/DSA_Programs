#include<iostream>
#include<vector>
#include<queue>
using namespace std;

class Solution {
  public:
    // Function to return Breadth First Traversal of given graph.
    vector<int> bfs(vector<vector<int>> &adj) {
        int start = 0;
        vector<int> res;
        vector<bool> vis (adj.size(), false);
        queue<int> q;
        q.push(start);
        vis[start] = true;
        while(!q.empty()){
            int node = q.front();
            q.pop();
            res.push_back(node);
            for(int adjnode : adj[node]){
                if(!vis[adjnode]){
                    vis[adjnode] = true;
                    q.push(adjnode);
                }
            }
        }
        return res;
    }
};