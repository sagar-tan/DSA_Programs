#include<iostream>
#include<vector>
using namespace std;
class Solution {
    public:
        int maxSubArray_Unoptimised(vector<int>& nums) {
            int n = nums.size();
            int prevMax=nums[0];
            int maxSum = nums[0];
            for(int i=1; i < n; i++){
                int curr_sum = max(prevMax + nums[i], nums[i]);
                maxSum = max(curr_sum, maxSum);
                prevMax = curr_sum;
            }
            return maxSum;
        }
    };
int main(){

}