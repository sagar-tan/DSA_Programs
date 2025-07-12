#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;
int maxGoodSub(vector<int> arr, int k, int n){
    unordered_map<int, int> freq;
    int l = 0, r = 0;
    int maxSum = 0, currsum = 0;
    while(r<n){
        currsum += arr[r];
        freq[arr[r]]++;
        while(freq.size()>k){
            freq[arr[l]]--;
            currsum -= arr[l];
            if(freq[arr[l]]==0){
                freq.erase(arr[l]);
            }
            l++;
        }
        maxSum = max(maxSum, currsum);
        r++;
    }
    return maxSum;
}
void display(vector<int> arr, int n){//just checking!
    for(int i = 0; i< n; i++){
        cout << arr[i];
    }
}
int main(){
    int n, k;
    cin >> n >> k;    
    vector<int> arr;
    for(int i =0 ;i<n;i++){
        int x;
        cin >> x;
        arr.push_back(x); 
    }

    int res = maxGoodSub(arr, k, n);
    cout << res;

}