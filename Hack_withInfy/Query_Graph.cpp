#include<iostream>
#include<vector>
#include<map>
#include<set>

using namespace std;
const int MAXN = 100005;
int parent[MAXN], rank1[MAXN];

int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

// Union by Rank, returns new root
int union_sets(int x, int y) {
    if (rank1[x] < rank1[y]) {
        parent[x] = y;
        return y;
    } else if (rank1[x] > rank1[y]) {
        parent[y] = x;
        return x;
    } else {
        parent[x] = y;
        rank1[y]++;
        return y;
    }
}