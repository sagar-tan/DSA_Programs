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
        cout << "enter n2" << endl;
        cin >> n2;

    }
    void add(){
        cout <<"answer: "<< n1+n2;
    }

};
int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    Person p1;
    p1.data_set();
    p1.add();
   
}