#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

int countEvenThreeDigitNumbers(vector<int>& digits) {
    set<int> uniqueNumbers;
    int n = digits.size();

    // Generate all permutations of 3-digit numbers
    for (int i = 0; i < n; ++i) {
        if (digits[i] == 0) continue; // No leading zero

        for (int j = 0; j < n; ++j) {
            if (j == i) continue;

            for (int k = 0; k < n; ++k) {
                if (k == i || k == j) continue;

                if (digits[k] % 2 == 0) { 
                    int num = digits[i] * 100 + digits[j] * 10 + digits[k];
                    uniqueNumbers.insert(num);
                }
            }
        }
    }

    return uniqueNumbers.size();
}

int main() {
    vector<int> digits = {2, 2, 2};
    cout << countEvenThreeDigitNumbers(digits) << endl; // Output: 12
    return 0;
}
