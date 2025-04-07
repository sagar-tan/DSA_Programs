#include<iostream>
#include<vector>
using namespace std;

int fxn(string s1, int i, string s2, int j, vector<vector<int>>& dp){
    if (i==0||j==0){
        return 0;
    }
    if(dp[i][j]!=-1) return dp[i][j];
    if(s1[i-1]==s2[j-1]){
        return dp[i][j]=1+fxn(s1, i-1, s2, j-1, dp);
    }
    else{
        return dp[i][j]=max(fxn(s1, i-1, s2, j, dp), fxn(s1, i, s2, j-1, dp));
    }
}

int main(){
    string s1 = "ABCAB";
    string s2 = "AECB";
    int i = s1.size();
    int j = s2.size();
    vector<vector<int>> dp(i+1, vector<int>(j+1, -1));
    int n = fxn(s1, i, s2, j, dp);
    cout << "Length of LCS: " << n << endl;
    return 0;
} 