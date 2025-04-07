#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int totalSum = 0;
        for (int val : nums) {
            totalSum += val;
        }
        
        // If target is out of bounds or totalSum+target is odd, no solution exists
        if (abs(target) > totalSum || (totalSum + target) % 2 != 0) {
            return 0;
        }
        
        // Define a new target for subset sum
        int newTarget = (totalSum + target) / 2;
        
        // DP array to store memoization results
        vector<vector<int>> dp(nums.size(), vector<int>(2*totalSum+1, -1));
        
        return solveMemo(nums, nums.size(), target, 0, 0, dp, totalSum);
    }
    
private:
    int solveMemo(vector<int>& nums, int n, int target, int index, int currSum, 
                  vector<vector<int>>& dp, int totalSum) {
        // If we've processed all elements
        if (index == n) {
            // Return 1 if we've reached the target sum, 0 otherwise
            return currSum == target ? 1 : 0;
        }
        
        // Check if result already calculated
        if (dp[index][currSum + totalSum] != -1) {
            return dp[index][currSum + totalSum];
        }
        
        // Two choices: add current element or subtract current element
        int addWays = solveMemo(nums, n, target, index + 1, currSum + nums[index], dp, totalSum);
        int subtractWays = solveMemo(nums, n, target, index + 1, currSum - nums[index], dp, totalSum);
        
        // Store result in dp table and return
        return dp[index][currSum + totalSum] = addWays + subtractWays;
    }
};

int main() {
    Solution sol;
    vector<int> nums = {1, 1, 1, 1, 1};
    int target = 3;
    
    cout << "Number of ways to achieve target sum " << target << ": " 
         << sol.findTargetSumWays(nums, target) << endl;
    
    return 0;
} 