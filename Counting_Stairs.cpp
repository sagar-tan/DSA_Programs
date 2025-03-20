#include<bits/stdc++.h>
using namespace std;

void fxn(int n,string str, vector<string>& arr){
    if(n==0){
        arr.push_back(str);
        return;
    }
    if(n<0){
        return;
    }
    fxn(n-1,str+"1", arr);
    fxn(n-2, str+"2", arr);
}
int main(){
    int n = 3;
    vector<string>ans;
    string curr= "";
    fxn(n, curr, ans);
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i];
        if (i != ans.size() - 1) {
            cout << ", ";
        }
    }
    return 0;
}