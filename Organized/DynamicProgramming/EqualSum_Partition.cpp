#include <iostream>
#include <vector>
using namespace std;

// Function to check if the array can be divided into two subsets with equal sum
bool canDivide(const vector<int>& nums, int sum) {
    return (sum % 2 == 0);
}

// Recursive function for subset sum
bool canPartition(const vector<int>& nums, int idx, int target) {
    if (target == 0) return true; // Found a subset with required sum
    if (target < 0 || idx < 0) return false; // Out of bounds or invalid sum

    // Include the current element in the subset
    bool pick = canPartition(nums, idx - 1, target - nums[idx]);
    // Exclude the current element from the subset
    bool notPick = canPartition(nums, idx - 1, target);

    return (pick || notPick);
}

// Top-Down DP function
int canPartitionTD(const vector<int>& nums, int idx, int target, vector<vector<int>>& dp) {
    if (target == 0) return 1; // Subset with required sum found
    if (target < 0 || idx >= nums.size()) return 0; // Out of bounds or invalid sum
    if (dp[idx][target] != -1) return dp[idx][target];
    
    // Include the current element in the subset
    bool pick = canPartitionTD(nums, idx + 1, target - nums[idx], dp);
    // Exclude the current element from the subset
    bool notPick = canPartitionTD(nums, idx + 1, target, dp);
    
    // Store and return the result
    dp[idx][target] = (pick || notPick) ? 1 : 0;
    return dp[idx][target];
}

// Bottom-Up DP function
int canPartitionBU(const vector<int>& nums, int n, int target) {
    vector<vector<int>> dp(n + 1, vector<int>(target + 1, 0));
    
    // Initialize DP for target = 0
    for (int i = 0; i <= n; i++) dp[i][0] = 1;
    
    for (int i = n - 1; i >= 0; i--) {
        for (int t = 1; t <= target; t++) {
            int pick = (t - nums[i] >= 0) ? dp[i + 1][t - nums[i]] : 0;
            int notPick = dp[i + 1][t];
            dp[i][t] = (pick || notPick);
        }
    }
    
    return dp[0][target];
}

int main() {
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;

    vector<int> nums(n);
    int sum = 0;

    cout << "Enter the elements of the array:" << endl;
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
        sum += nums[i];
    }

    if (!canDivide(nums, sum)) {
        cout << "Cannot partition into two subsets with equal sum." << endl;
        return 0;
    }

    int target = sum / 2;

    // Recursive solution
    if (canPartition(nums, n - 1, target)) {
        cout << "Can partition into two subsets with equal sum (Recursive)." << endl;
    } else {
        cout << "Cannot partition into two subsets with equal sum (Recursive)." << endl;
    }

    // Top-Down DP solution
    vector<vector<int>> dp(n + 1, vector<int>(target + 1, -1));
    if (canPartitionTD(nums, 0, target, dp)) {
        cout << "Can partition into two subsets with equal sum (Top-Down DP)." << endl;
    } else {
        cout << "Cannot partition into two subsets with equal sum (Top-Down DP)." << endl;
    }

    // Bottom-Up DP solution
    if (canPartitionBU(nums, n, target)) {
        cout << "Can partition into two subsets with equal sum (Bottom-Up DP)." << endl;
    } else {
        cout << "Cannot partition into two subsets with equal sum (Bottom-Up DP)." << endl;
    }

    return 0;
} 