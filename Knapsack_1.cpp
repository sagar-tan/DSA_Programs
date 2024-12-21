#include<iostream>
#include<vector>
#include<limits.h>
int fxn(int cap, vector<int>& wt, vector<int>& val, int n){
if (n==0){
    if(wt[n]<=cap){
        return val[0];
    }
}
vector<vector<int>> dp(n+1, vector<int>(cap+1));
for(int i= wt[0];i<=cap;i++){
    dp[0][i]=val[0];
}
for(int i=1;i<n;i++){
    for(int w=1;w<=cap;w++){
        int not_pick = dp[i-1][w];
        int pick = INT_MIN;
        if(wt[i]<w){
            pick = val[i]+dp[i-1][w-wt[i]];
        }
        dp[i][w] = max(not_pick, pick);
    }
    return dp[n-1][cap]
}
}
int main(){
    
}