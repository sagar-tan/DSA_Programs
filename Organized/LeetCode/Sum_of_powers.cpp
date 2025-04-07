#include <iostream>
using namespace std;

bool checkPowersOfThree(int n) {
    while (n > 0) {
        if (n % 3 == 2) {
            return false;
        }
        n = n / 3;
        cout << n;
    }
    return true;
}

int main() {
    int n;
    cout << "Enter a number: ";
    cin >> n;
    
    if (checkPowersOfThree(n)) {
        cout << n << " can be represented as a sum of distinct powers of 3." << endl;
    } else {
        cout << n << " cannot be represented as a sum of distinct powers of 3." << endl;
    }
    
    return 0;
}
