
class Solution {
public:
    int fxn(int n,vector<int> &dp){
        if(n==0||n==1){
            return 1;
        }
        if(dp[n]!=-1) return dp[n];
        return dp[n]=fxn(n-1, dp)+fxn(n-2, dp);
    }
    int climbStairs(int n) {
        vector<int> dp(n+1, -1);
        return fxn(n, dp);
        
        
    }
};

//Trying Using DP Using Iteration

class Solution {
public:
    int climbStairs(int n) {
        vector<int> dp(n+1,0);
        dp[0]=dp[1]=1;
        for(int i=2; i<=n; i++){
            dp[i]= dp[i-1]+dp[i-2];
        }
        return dp[n];
    }
  
};