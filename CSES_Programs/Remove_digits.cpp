#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin >> n;
    int temp = n;
    int steps=0;
    int maxDigit=0;
    while(n>0){
        while(temp>0){
            maxDigit = max(maxDigit, temp%10);
            temp/=10;
        }
        n-=maxDigit;
        steps++;
    }
    cout<<steps;
}