#include<bits/stdc++.h>
using namespace std;
class Person{
private:
    string name;
    int age;
public:
    void data_set(string n, int a){
        name = n;
        age = a;
    }
    void show(){
        cout << name << " " << age;
    }

};
int main(){
    freopen("output.txt", "w", stdout);

    Person p1;
    p1.data_set("alice", 15);
    p1.show();
   
}