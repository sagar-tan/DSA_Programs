
#include<bits/stdc++.h>
using namespace std;
bool canPart_rc(int index, vector<int>& arr,int target){//Top Down
    if (target==0){
        return 1;
    }
    if (target<0){
        return false;
    }
    if (index>=arr.size()){
        return false;
    }
    bool include = canPart_rc(index +1, arr, target-arr[index]);
    bool exclude = canPart_rc(index +1, arr, target);
    return include||exclude;
}







int canPart_TD(vector<vector<int>>&dp, int index, vector<int>& arr, int target){
    if(target<=0||index>=arr.size())return 0;
    if (target) return 1;
    if(dp[index][target]!=-1) return dp[index][target];
    bool include = canPart_TD(dp, index + 1, arr, target-arr[index]);
    bool exclude = canPart_TD(dp, index + 1, arr, target);
    dp[index][target] = (include||exclude);
}


int main(){
//    vector<int> arr;
//   for(int i=0, i<=n;i++){
//     cout<<"Enter element"<<i<<endl;
//    cin>>arr[i];
//}
    vector<int> arr = {1,5,11,5};
    int n = arr.size();
    int totalsum = 0;
    for(int i=0;i<=n-1;i++){
        totalsum+=arr[i];
    }
    if(totalsum & 1){
        cout<<"Unable to Divide";
      return 0;
    }
    int target = totalsum/2;
    int index = 0;
    vector<vector<int>> dp(n+1, vector<int>(target+1, -1));
    bool j = canPart_TD(dp, index, arr, target);
    if(j){
        cout<<"Can be Divided";
    }
  return 0;
    

}
