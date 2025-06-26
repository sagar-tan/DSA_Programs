#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    vector<vector<int>> buildAdjList(int v, vector<vector<int>> &edges) {
        vector<vector<int>> adj(v);
        for (int i = 0; i < edges.size(); i++) {
            int from = edges[i][0];
            int to = edges[i][1];
            adj[from].push_back(to);
            adj[to].push_back(from);
        }
        return adj;
    }
    void bfs(int start, vector<vector<int>> &adj, vector<bool> &vis) {
        queue<int> q;
        q.push(start);
        vis[start] = true;
        while(!q.empty()){
            int node = q.front();
            q.pop();
            for(int adjnode : adj[node]){
                if(!vis[adjnode]){
                    vis[adjnode] = true;
                    q.push(adjnode);
                }
            }
        }
    }
    int countComponents(int n, vector<vector<int>>& edges) {
        vector<vector<int>>adj = buildAdjList(n, edges);
        vector<bool> vis (adj.size(), false);
        int res;
        for(int i = 0; i<vis.size();i++){
            if(!vis[i]){
                res++;
                bfs(i, adj, vis);
            }
        }
        return res;
    }
};
