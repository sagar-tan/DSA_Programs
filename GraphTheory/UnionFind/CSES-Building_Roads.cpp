#include <bits/stdc++.h>
using namespace std;

const int N = 1e5+5;
int parent[N], rank1[N];

int find(int x) {
    if (x != parent[x])
        parent[x] = find(parent[x]);
    return parent[x];
}

bool unionSet(int a, int b) {
    int root_a = find(a);
    int root_b = find(b);
    if (root_a == root_b) return false;

    if (rank1[root_a] < rank1[root_b])
        parent[root_a] = root_b;
    else if (rank1[root_a] > rank1[root_b])
        parent[root_b] = root_a;
    else {
        parent[root_b] = root_a;
        rank1[root_a]++;
    }
    return true;
}

int main() {
    int n, m;
    cin >> n >> m;

    // Init
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        rank1[i] = 0;
    }

    // Read and union
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        unionSet(a, b);
    }

    // Find unique components
    vector<int> reps;
    for (int i = 1; i <= n; i++) {
        if (find(i) == i)
            reps.push_back(i);
    }

    // Output
    int newRoads = reps.size() - 1;
    cout << newRoads << '\n';
    for (int i = 1; i < reps.size(); i++) {
        cout << reps[i - 1] << " " << reps[i] << '\n';
    }

    return 0;
}
