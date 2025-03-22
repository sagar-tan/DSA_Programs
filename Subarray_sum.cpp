#include<bits/stdc++.h>
using namespace std;
void fxn(int i, int sum, vector<int> arr, vector<int> ans){
    if(i == arr.size()){
        ans.push_back(sum);
        return;
    }
    fxn(i+1, sum, arr, ans);//not pick  
    fxn(i+1, sum+arr[i], arr, ans);//pick
}
int main(){
    vector<int> arr = {9, 4};
    vector<int> ans;
    fxn(0,0,arr, ans);
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i];
        if (i != ans.size() - 1) {
            cout << ", ";
        }
    }
}