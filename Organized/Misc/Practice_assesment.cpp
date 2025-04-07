#include<bits/stdc++.h>
#include<math.h>
using namespace std;
class Person{
private:
    int n1;
    int n2;
public:
    void data_set(){
        cout << "enter total days" << endl;
        cin >> n1;

    }
    void finding_years(){
        int  years = n1/365;
        n1%=365;
        int months = n1/30;
        n1%=30;        
        cout <<"Years: "<< years<< endl;
        cout <<"months: "<< months<<endl;
        cout <<"days: "<<n1;

    }

};
int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    Person p1;
    p1.data_set();
    p1.finding_years();
   
}