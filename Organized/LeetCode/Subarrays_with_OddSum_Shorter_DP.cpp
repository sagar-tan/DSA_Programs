#include<iostream>
#include<vector>// Code Explanation to be Published Separately
using namespace std;
void printArr(const vector<int>& arr){
    for(int i = 0; i< arr.size();i++){
        cout << arr[i] << " ";
        
    }
}
int returnSUM(vector<int>& arr){
    const int MOD = 1e9+7;
    int n = arr.size();
    vector<int> OddSum(n), EvenSum(n);
    for(int i=0;i<n;i++){
        arr[i]= arr[i]%2;
    }

    if (arr[n-1] == 0){
        EvenSum[n-1]=1;
    }
    else{
        OddSum[n-1]=1;
    }
    printArr(arr);
    cout<<endl;
    for(int i=n-2;i>=0;i--){
        if(arr[i] == 1){// what the actual fuck mate, i was assigning the value instead of checking, WTH............. fuck my life
            OddSum[i] = (1 + EvenSum[i+1]) % MOD;
            EvenSum[i] = OddSum[i+1];
            cout<<"the element is odd as we have 1 in the remainder so well, even sum at element "<< i << " will be " << OddSum[i] << endl;
            
        }
        else{
            EvenSum[i] = (1 + EvenSum[i+1]) % MOD;
            OddSum[i] = OddSum[i+1];
            cout<<"the element is even so well, even sum at element "<< i << " will be " << EvenSum[i] << endl;
        }
    }
    printArr(OddSum);
    cout<<endl;
    int count = 0;
    for(int i=0;i<n;i++){
        count = count + OddSum[i];
        count %= MOD;
    }
    return count;
}
int main(){
    vector<int> arr = {2,4,6};
   cout << returnSUM(arr);
return 0;
}