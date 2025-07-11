#include<iostream>
#include<vector>
using namespace std;
const int MAXN = 1e5; //constraint
int tree[4*MAXN];
int maxtree[4   *MAXN];
int arr[MAXN];
void build(int node, int l, int r){
    if(l==r){
        tree[node] = arr[l];
        return;
    }
    int mid = (l+r)/2;
    build(2*node, l, mid);
    build(2*node+1, mid+1, r);
    tree[node] = tree[2*node]+tree[2*node+1];
    maxtree[node] = max(maxtree[2*node],maxtree[2*node+1]) ;
}
int addQuery(int node, int l, int r, int ql, int qr){//range sum query logN
    if(qr<l || ql>r){
        return 0;
    }
    if(ql<=l && qr>=r){
        return tree[node];
    }
    int mid = (l+r)/2;
    return addQuery(2*node, l, mid, ql, qr) + addQuery(2*node+1, mid+1, r, ql, qr);
}
void updateQuery(int node,int idx, int val, int l, int r){
    if(l==r){
        tree[node] = val;
        maxtree[node] = val;
        return;
    }
    int mid = (l+r)/2;
    if(idx<=mid){
        updateQuery(2*node, idx, val, l, mid);
    }
    else{
        updateQuery(2*node+1, idx, val, mid+1, r);
    }
    tree[node] = tree[2*node]+tree[2*node+1];
    maxtree[node] = max(maxtree[2*node], maxtree[2*node+1]);
}
void modQuery(int node, int ql, int qr, int l, int r, int x){
    if(maxtree[node]<x || ql>r || qr < l) return;
    if(l==r){
        tree[node] %= x;
        maxtree[node] = tree[node];
        return;
    }
    int mid = (l+r)/2;
    modQuery(2*node, ql, qr, l, mid, x);
    modQuery(2*node+1, ql, qr, mid+1, r, x);
    tree[node] = tree[2*node]+tree[2*node+1];
    maxtree[node] = max(maxtree[2*node], maxtree[2*node+1]);
    
}
int main(){
    int n, m;
    cin >> n >> m;
    for(int i=0; i<n;i++){
        cin >> arr[i];
    }
    build(1, 0, n-1);
    while(m--){
        int query;
        cin >> query;
        if(query == 1){
            int m, n;
            cin >> m >> n;
            int res = addQuery(1, 0, n-1, m-1, n-1);
            cout << res <<endl;
        }
        else if(query == 2){
            int m, n, x;
            cin >> m >> n>> x;
            modQuery(1, m-1, n-1, 0, n-1, x);
        }
        else if(query == 3){
            int i, x;
            cin >> i >> x;
            updateQuery(1, i-1, x, 0, n-1);
        }
    }


}