#include<iostream>
#include<vector>
bool fxn(int index, vector<int>& arr, int n, int target){
    if (target==0){
        return true;
    }
    if (target<0){
        return false;
    }
    if (index>=n){
        return false;
    }
    bool include = fxn(index +1, arr, n, target-arr[index])
    bool exclude = fxn(index +1, arr, n, target);
    return (include||exclude);


}
int main(){
    vector<int> arr = ()
    if(totalsum&1) return 0;
    int target = totalsum/2;
    fxn(index, arr, n, target)

}
//using dp