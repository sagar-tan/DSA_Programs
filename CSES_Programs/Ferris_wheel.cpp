#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, x;
    cout << "Enter a number";
    cin >> n >> x;
    vector<int> weight(n);
    for (int i = 0; i < n; ++i)
        cin >> weight[i];
    sort(weight.begin(), weight.end());
    int i = 0, j = n - 1, gondolas = 0;

    while (i <= j) {
        if (weight[i] + weight[j] <= x) {
            i++;
            j--;
        } else {
            j--;
        }
        gondolas++;
    }

    cout << gondolas << endl;
    return 0;
}
