#include<iostream>
using namespace std;
int find_max(int a, int b, int c){
    if(a>=b&&a>=c){//a>=b:false
        return a;
    }
    if(b>=a&&b>=c){//b>=a:true.....2>=3:false
        return b;
    }
    if(c>=a&&c>=b){
        return c;
    }
}
int find_mx_2(int a, int b, int c){
    int x = find_max(a,b,c);
    if(a<x&& a>= b || a>= c){
        return a;
    }
    else if(b<x&& b>= a || b>= a){
        return b;
    }
    else if(c<x && c>= b || c>= a){
        return c;
    }
}
int main(){
    int a = 5;
    int b = 3;  
    int c = 5;
    cout << "max number : " << find_max(a,b,c) << endl;
    cout << "2nd max number : " << find_mx_2(a,b,c) << endl;
    


}