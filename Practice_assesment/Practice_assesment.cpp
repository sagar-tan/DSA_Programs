#include<bits/stdc++.h>
using namespace std;
class Person{
private:
    int n1;
    int n2;
public:
    void data_set(){
        cout << "enter n1" << endl;
        cin >> n1;

    }
    void add(){
        int area = (3.14)*n1*n1;
        int circum = 2*(3.14)*n1;
        cout <<"area: "<< area << endl;
        cout << "circumference: " << circum;

    }

};
int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    Person p1;
    p1.data_set();
    p1.add();
   
}