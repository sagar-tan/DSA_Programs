#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v, w;
    bool operator<(const Edge &other) const {
        return w < other.w;
    }
};

const int N = 1e5 + 5;
int parent[N], rank1[N];

int find(int x) {
    if (x != parent[x]) parent[x] = find(parent[x]);
    return parent[x];
}

bool unionSet(int a, int b) {
    int root_a = find(a);
    int root_b = find(b);
    if (root_a == root_b) return false;

    if (rank1[root_a] < rank1[root_b]) {
        parent[root_a] = root_b;
    } else if (rank1[root_a] > rank1[root_b]) {
        parent[root_b] = root_a;
    } else {
        parent[root_b] = root_a;
        rank1[root_a]++;
    }
    return true;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<Edge> edges;
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        rank1[i] = 0;
    }

    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        edges.push_back({a, b, c});
    }

    sort(edges.begin(), edges.end());

    long long totalCost = 0;
    int edgesUsed = 0;

    for (auto &e : edges) {
        if (unionSet(e.u, e.v)) {
            totalCost += e.w;
            edgesUsed++;
            if (edgesUsed == n - 1) break;
        }
    }

    if (edgesUsed == n - 1)
        cout << totalCost << "\n";
    else
        cout << "IMPOSSIBLE\n";

    return 0;
}



 