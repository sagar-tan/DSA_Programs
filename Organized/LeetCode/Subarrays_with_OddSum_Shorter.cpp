#include<iostream>
#include<vector>
using namespace std;
void printArr(const vector<int>& arr){
    for(int i = 0; i< arr.size();i++){
        cout << arr[i] << " ";
        cout << endl;
    }
}
void returnSUM(vector<int>& arr){
    const int MOD = 1e9 + 7;// means 10^9
        int n = arr.size();
        int count = 0;

        // Generate all possible subarrays
        for (int startIndex = 0; startIndex < n; startIndex++) {
            int currentSum = 0;
            // Iterate through each subarray starting at startIndex
            for (int endIndex = startIndex; endIndex < n; endIndex++) {
                currentSum += arr[endIndex];
                cout <<startIndex<< ":i  , "<< endIndex<<":j  ,   { "<< arr[endIndex] << " }  ;  ";
                cout << endl << "Current SUM :"<< currentSum <<endl;
                if (currentSum % 2 != 0) {
                    count++;
                }
            }
            cout << endl;
        }

        cout << count % MOD;

}
int main(){
    vector<int> arr = {1,3,5,6};
    printArr(arr);
    returnSUM(arr);
return 0;
}