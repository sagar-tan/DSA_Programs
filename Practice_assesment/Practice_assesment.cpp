#include<bits/stdc++.h>
#include<math.h>
using namespace std;
class Person{
private:
    int n1;
    int n2;
public:
    void data_set(){
        cout << "enter Rupees" << endl;
        cin >> n1;

    }
    void add(){
        int paise = 100*n1; 
        cout <<"paise: "<< paise;

    }

};
int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    Person p1;
    p1.data_set();
    p1.add();
   
}