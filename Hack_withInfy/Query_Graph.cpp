#include<iostream>
#include<vector>
#include<map>
#include<set>

using namespace std;
const int MAXN = 100005;
int parent[MAXN], rank1[MAXN];
map<int, set<int>> componentMap;
map<int, int> componentBeauty;

int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

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

int main(){
    int n, q;
    cin >> n >> q;
    for(int i = 1; i<=n; i++){
        parent[i] = i;
        rank1[i] = 0;
        set<int> s;
        s.insert(i);
        componentMap[i] = s;
        componentBeauty[i] = 1;
    }
    long long totalBeauty = 0;
    while(q--){
        int type, u, v;
        cin >> type >> u >> v;
        if(type == 1){
            int ru = find(u);
            int rv = find(v);
            if(ru != rv){
                int newRoot = union_sets(ru, rv);
                int oldRoot = (newRoot == ru) ? rv:ru;
                set<int> & setNew = componentMap[newRoot];
                set<int> & setOld = componentMap[oldRoot];
                int beauty = componentBeauty[newRoot];
                for(int node : setOld){
                    bool hasLeft = setNew.count(node - 1);
                    bool hasRight = setNew.count(node + 1);
                    if(hasLeft && hasRight){
                        beauty--;
                    }
                    else if(!hasLeft && !hasRight){
                        beauty++;
                    }
                    setNew.insert(node);
                }
                componentMap[newRoot] = setNew;
                componentMap.erase(oldRoot);
                componentBeauty[newRoot] = beauty;
                componentBeauty.erase(oldRoot);
            }
        }
        else if (type == 2) {
            int root = find(u);
            totalBeauty += componentBeauty[root];
        }
    }
    cout << totalBeauty << endl;
    return 0;
    
}