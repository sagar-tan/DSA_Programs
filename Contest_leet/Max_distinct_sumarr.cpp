#include <bits/stdc++.h>
using namespace std;

int maxUniqueSubarraySum(vector<int>& nums) {
    unordered_set<int> uniqueElements;
    int maxSum = 0, currentSum = 0;
    int left = 0;
    
    for (int right = 0; right < nums.size(); ++right) {
        while (uniqueElements.count(nums[right])) {
            uniqueElements.erase(nums[left]);
            currentSum -= nums[left];
            left++;
        }
        uniqueElements.insert(nums[right]);
        currentSum += nums[right];
        maxSum = max(maxSum, currentSum);
    }
    
    return maxSum;
}

int main() {
    vector<int> nums = {1, 1, 0, 1, 1};
    cout << "Maximum sum of unique subarray: " << maxUniqueSubarraySum(nums) << endl;
    return 0;
}
