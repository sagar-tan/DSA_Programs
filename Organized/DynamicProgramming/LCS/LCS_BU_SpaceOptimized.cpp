//Space Optimisation for Longest Common Subsequence
#include<iostream>
#include<vector>
using namespace std;

int main(){
    string s1 = "ABCAB";
    string s2 = "AECB";
    int m = s1.size();
    int n = s2.size();
    vector<int> dp(n+1, 0);//prev
    vector<int> dp2(n+1, 0);//next
    
    for(int i=1; i<=m; i++){
        for(int j=1; j<=n; j++){
            if(s1[i-1]==s2[j-1]){
                dp2[j] = dp[j-1]+1;
            }
            else{
                dp2[j] = max(dp2[j-1], dp[j]);
            }
        }
        dp = dp2;
    }
    
    cout << "Length of LCS: " << dp2[n] << endl;
    return 0;
} 