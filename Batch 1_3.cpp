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
//O/1 KnapSack problem
#include<iostream>
#include<vector>
int fxn(vector<int>& weight, vector<int>& profit, int w, int x, int i, int max){
    if(x==0){
        return 0;
    }
    if(x==1){
        if(weight[x]<=cap){
            return profit[0];
        }
        else{
            return 0;
        }
    if 
    }

}
int main(){
    int x  = 3;//no of items
    int capacity = 5;//Capacity
    vector<int> weight(n, 0);
    vector<int> profit(n, 0);
    for(int i==0;i<x;i++){
        cin>>weight[i];
        cin>>profit[i];
    }

}