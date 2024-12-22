#include<iostream>
using namespace std ;
int fxn(string s1, int i, string s2, int j){
    if (i==0||j==0){
        return 0;
    }
    if(s1[i-1]==s2[j-1]){
        return 1+fxn(s1, i-1, s2, j-1);
    }
    else{
        return max(fxn(s1, i-1, s2, j), fxn(s1, i, s2, j-1));
    }
}
int main(){
    string s1 = "ABCAB";
    string s2 = "AECB";
    int i = s1.size();
    int j = s2.size();
    int n = fxn(s1, i, s2, j);
    cout << n;
}