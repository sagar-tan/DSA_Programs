/*
#include<bits/stdc++.h>
using namespace std;
bool fxn(vector<vector<int>>& dp, int index, vector<int>& arr,int n,int target){//Top Down
    if (target==0){
        return 0;
    }
    if (target<0){
        return false;
    }
    if (index>=n){
        return false;
    }
    bool include = fxn(dp, index +1, arr, n, target-arr[index]);
    bool exclude = fxn(dp, index +1, arr, n, target);
    return include||exclude;


}
/*
int fxn(vector<vector<int>>& dp, int index, vector<int>& arr, int n, int target){

}


int main(){
//    vector<int> arr;
//   for(int i=0, i<=n;i++){
//     cout<<"Enter element"<<i<<endl;
//    cin>>arr[i];
//}
    vector<int> arr = {1,5,11,5};
    int n = arr.size();
    int totalsum = 0;
    for(int i=0;i<=n;i++){
        totalsum+=arr[i];
    }
    if(totalsum & 1) return 0;
    int target = totalsum/2;
    int index = 0;

    vector<vector<int>> dp(n+1, vector<int>(target+1, -1));
    
    bool j = fxn(dp, index, arr, n, target);
    cout<<
    

}
*/


//aayushi java code
#include <iostream>
#include <vector>
using namespace std;

// Function to check if the array can be divided into two subsets with equal sum
bool Candivide(const vector<int>& nums, int sum) {
    return (sum % 2 == 0);
}

// Recursive function for subset sum
bool canpartition(const vector<int>& nums, int idx, int target) {
    if (target == 0) return true; // Found a subset with required sum
    if (target < 0 || idx < 0) return false; // Out of bounds or invalid sum

    // Include the current element in the subset
    bool pick = canpartition(nums, idx - 1, target - nums[idx]);
    // Exclude the current element from the subset
    bool notpick = canpartition(nums, idx - 1, target);

    return (pick || notpick);
}

// Top-Down DP function
int canpartitionTD(const vector<int>& nums, int idx, int target, vector<vector<int>>& dp) {
    if (target == 0) return 1; // Subset with required sum found
    if (target < 0 || idx >= nums.size()) return 0; // Out of bounds or invalid sum
    if (dp[idx][target] != -1) return dp[idx][target];
    // Include the current element in the subset
    bool pick = canpartitionTD(nums, idx + 1, target - nums[idx], dp);
    // Exclude the current element from the subset
    bool notpick = canpartitionTD(nums, idx + 1, target, dp);
    // Store and return the result
    dp[idx][target] = (pick || notpick) ? 1 : 0;
    return dp[idx][target];
}

// Bottom-Up DP function
int canpartitionBU(const vector<int>& nums, int n, int target) {
    vector<vector<int>> dp(n + 1, vector<int>(target + 1, 0));
    // Initialize DP for target = 0
    for (int i = 0; i <= n; i++) dp[i][0] = 1;
    for (int i = n - 1; i >= 0; i--) {
        for (int t = 1; t <= target; t++) {
            int pick = (t - nums[i] >= 0) ? dp[i + 1][t - nums[i]] : 0;
            int notpick = dp[i + 1][t];
            dp[i][t] = (pick || notpick);
        }
    }
    return dp[0][target];
}

int main() {
    int x;
    cout << "Enter the number of elements: ";
    cin >> x;

    vector<int> weight(x);
    int sum = 0;

    cout << "Enter the elements of the array:" << endl;
    for (int i = 0; i < x; i++) {
        cin >> weight[i];
        sum += weight[i];
    }

    if (!Candivide(weight, sum)) {
        cout << "Cannot partition into two subsets with equal sum." << endl;
        return 0;
    }

    int target = sum / 2;

    // Recursive solution
    if (canpartition(weight, x - 1, target)) {
        cout << "Can partition into two subsets with equal sum (Recursive)." << endl;
    } else {
        cout << "Cannot partition into two subsets with equal sum (Recursive)." << endl;
    }

    // Top-Down DP solution
    vector<vector<int>> dp(x + 1, vector<int>(target + 1, -1));
    if (canpartitionTD(weight, 0, target, dp)) {
        cout << "Can partition into two subsets with equal sum (Top-Down DP)." << endl;
    } else {
        cout << "Cannot partition into two subsets with equal sum (Top-Down DP)." << endl;
    }

    // Bottom-Up DP solution
    if (canpartitionBU(weight, x, target)) {
        cout << "Can partition into two subsets with equal sum (Bottom-Up DP)." << endl;
    } else {
        cout << "Cannot partition into two subsets with equal sum (Bottom-Up DP)." << endl;
    }

    return 0;
}


