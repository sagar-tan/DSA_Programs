/*
Count partitions with even sum difference
[10,10,3,7,6] gives 4 
[10], [10, 3, 7, 6] with a sum difference of 10 - 26 = -16, which is even.
[10, 10], [3, 7, 6] with a sum difference of 20 - 16 = 4, which is even.
[10, 10, 3], [7, 6] with a sum difference of 23 - 13 = 10, which is even.
[10, 10, 3, 7], [6] with a sum difference of 30 - 6 = 24, which is even.

*/
#include <bits/stdc++.h>
#include <vector>
using namespace std;
class Solution {
public:
        int countPartitions(vector<int>& nums) {
        int totalSum = 0;
        for (int num : nums) {
            totalSum += num; // Calculate the total sum of the array
        }

        int leftSum = 0, count = 0;
        for (int i = 0; i < nums.size() - 1; i++) {
            leftSum += nums[i]; // Incrementally calculate the left sum
            int rightSum = totalSum - leftSum; // Right sum is the remaining part

            int diff = abs(leftSum - rightSum); // Difference of sums
            if (diff % 2 == 0) { // Check if the difference is even
                count++;
            }
        }

        return count;
    }
};
int main() { 
    Solution s;
    vector<int> nums = {10, 10, 3, 7, 6};
    cout << s.countPartitions(nums) << endl;
    return 0;
}