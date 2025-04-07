#include<iostream>
#include<queue>
using namespace std;
void gen(int n){
    queue<string>q;
    q.push("1");
     for (int i = 1; i <= n; ++i) {
        string front = q.front();
        q.pop();
        cout << front << " ";
        q.push(front + "0");
        q.push(front + "1");
     }

}
int main() {
    int n;
    cout << "Enter n: ";
    cin >> n;
    cout << "Binary No's from 1 to " << n << " are: ";
    gen(n);
    return 0;
}
