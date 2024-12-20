//Bottom UP Dynamic Programming approach, using the table.
#include<iostream>
#include<vector>
using namespace std;
int main(){
    string s1 = "ABCAB";
    string s2 = "AECB";
    int m = s1.size();
    int n = s2.size();
    vector<vector<int>> dp(m+1, vector<int>(n+1, 0));
    for(int i=1;i<=m; i++){
        for(int j=1;j<=n;j++){
            if(s1[i-1]==s2[j-1]){
                dp[i][j] = dp[i-1][j-1]+1;
            }
            else{
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }
    int q = dp[m][n];
    cout<<q;

}
//Space Optimisation
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
    for(int i=1;i<=m; i++){
        for(int j=1;j<=n;j++){
            if(s1[i-1]==s2[j-1]){
                dp2[j] = dp[j-1]+1;
            }
            else{
                dp2[j] = max(dp2[j-1], dp[j]);
            }
        }
        dp=dp2;
    }
    int q = dp2[n];
    cout<<q;

}
