#include<iostream>
#include<vector>
using namespace std;
void printArr(const vector<int>& arr){
    for(int i = 0; i< arr.size();i++){
        cout << arr[i] << " ";
        cout << endl;
    }
}
int returnSUM(vector<int>& arr){
    const int MOD = 1e9+7;
    int n = arr.size();
    vector<int> OddSum(n);
    vector<int> EvenSum(n);
    for(int i=0;i<n;i++){
        arr[i]= arr[i]%2;
        OddSum[i] = 0;
        EvenSum[i] = 0;
    }
    if (arr[n-1 == 0]){
        EvenSum[n-1]= 1;
    }
    else{
        OddSum[n-1]=1;
    }
    for(int i=n-2;i>=0;i--){
        if(arr[i] == 0){
            EvenSum[i] = EvenSum[i+1]+1 % MOD;
            OddSum[i] = OddSum[i+1];
        }
        else if(arr[i] = 1){
            EvenSum[i] = OddSum[i+1];
            OddSum[i] = EvenSum[i+1]+1 % MOD;
        }
    }
    int count = 0;
    for(int i=0;i<n;i++){
        count+=OddSum[i];
        count %= MOD;
    }
    return count;

}
int main(){
    vector<int> arr = {1,3,5,6};
    printArr(arr);
   cout << returnSUM(arr);
return 0;
}