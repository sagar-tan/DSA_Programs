#include<iostream>
#include<string>
using namespace std;
int main(){
    string s;
    int n;
    cin >> n;
    cin >> s;
    int x  = s.size();
    if (x > n){
        cout << s[0] << x-2 << s[x-1];
    }
    else {
        cout << s;
    }
}


/*
correct output
*/


/*
#include<iostream>
#include<string>
using namespace std;
int main(){
    int n;
    cin >> n;
    string s;
    for (int i = 0; i < n; i++){
        cin >> s;
        if (s.length() > 10){
            cout << s[0] << s.length() - 2 << s[s.length() - 1] << endl;
        } else {
            cout << s << endl;
        }
    }
    return 0;
}
*/