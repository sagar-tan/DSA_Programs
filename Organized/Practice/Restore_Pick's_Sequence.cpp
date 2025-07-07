#include<iostream>
#include<vector>
using namespace std;
int query1(vector<int> &arr,int l,int r){
    int res=0;
    for(int i = l; i<=r;i++){
        res+=arr[i];
    }
    cout << res;
}
void query2(vector<int> &arr, int l, int r, int x){
    for(int i = l; i<=r;i++){
        arr[i]= arr[i] % x;
    }

}
void query3(vector<int> &arr, int k, int x){
    arr[k] = x;
}
int main(){
    int n, m;
    cin << n << m;
    vector<int> arr;
    for(int i=0; i<n; i++){
        cin >> arr[i];
    }
    int query;
    while(cin>>query){
        if(query==1){
            int l,r;
            cin >> l >> r;
            query1(arr, l+1, r+1);
        }
        else if(query==2){
            int l2,r2,x;
            cin >> l2 >> r2 >> x;
            query2(arr, l2+1, r2+1, x);
        }
        else if(query==3){
            int k, x2;
            cin >> k >> x2;
            query3(arr, k, x2);
        }
    }
    return 0;
}