#include<iostream>
#include<vector>
using namespace std;
void arr_get(vector<vector<int>>& prefixed, vector<int>& nums){
    int n = nums.size();
    prefixed.clear();
    for(int i=0;i<nums.size();i++){
        for(int j=i;j<nums.size(); j++){
            vector<int> temp;
            for(int k = i;k<=j;k++){
                temp.push_back(nums[k]);
            }
            prefixed.push_back(temp);
        }
    }
}
void printArr(const vector<vector<int>>& arr){
    for(int i = 0; i< arr.size();i++){
        for(int j = 0;j< arr[i].size(); j++){
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}
void returnSUM(vector<vector<int>>& prefixed){
    int sum = 0;
    for (int i = 0; i < prefixed.size(); i++){
        int temp = 0;
        for(int j =0;j<prefixed[i].size();j++){
            temp = temp + prefixed[i][j];
            cout <<i<< ": i, "<< j<<": j, "<< prefixed[i][j] << " ,";
        }
        cout << endl << "final iterated temp value: "<< temp << endl;
        if (temp % 2 != 0){
            sum++;
            cout << "sum is odd" << endl;
        }
        cout << "sum: " << sum << endl;
        temp = 0;
    }
    cout << sum;
}
int main(){
    vector<int> nums = {1,2,3,4,5,6,7};
    vector<vector<int>> arr;
    arr_get(arr, nums);
    printArr(arr);
    returnSUM(arr);
return 0;
}