#include<iostream>
using namespace std;
int main(){
    int x;
    cout << "enter your age for verification";
    cin >> x;
    if(x<=17){
        cout << "not eligivle";
    }
    else {
        cout << "you are eligible";
    }
}