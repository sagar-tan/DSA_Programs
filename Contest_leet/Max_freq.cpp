#include <vector>
#include <unordered_set>
#include <algorithm>
#include <climits>
#include <iostream>
using namespace std;

class Solution {
public:
    int maxFrequency(vector<int>& nums, int k) {
        int totalk = 0;
        for (int num : nums) {
            if (num == k) {
                totalk++;
            }
        }

        unordered_set<int> xva;
        for (int num : nums) {
            xva.insert(k - num);
        }

        int count = totalk;
        for (int x : xva) {
            int cur;
            if (x == 0) {
                cur = totalk;
            } else {
                vector<int> transf(nums.size(), 0);
                for (int i = 0; i < nums.size(); i++) {
                    if (nums[i] == k - x) {
                        transf[i] = 1;
                    } else if (nums[i] == k) {
                        transf[i] = -1;
                    } else if (nums[i] < k - x) {
                        transf[i] = 0;
                    }
                }
                int currMax = kadane(transf);
                cur = currMax + totalk;
            }
            count = max(count, cur);
        }
        return count;
    }

private:
    int kadane(const vector<int>& arr) {
        if (arr.empty()) {
            return 0;
        }
        int maxSoFar = arr[0];
        int currMax = arr[0];
        for (int i = 1; i < arr.size(); i++) {
            currMax = max(arr[i], currMax + arr[i]);
            maxSoFar = max(maxSoFar, currMax);
        }
        return maxSoFar;
    }

};
int main() {
    Solution s;
    vector<int> nums = {1, 2, 4};
    int k = 5;
    cout << s.maxFrequency(nums, k) << endl;
    return 0;
}