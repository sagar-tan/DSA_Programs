#include<iostream>
#include<vector>
#include<set>
using namespace std;
int find_k(vector<int>& arr, int k){
    set<int> s (arr.begin(), arr.end());
    vector<int> v (s.begin(), s.end());
    return v[k-1];
}
void reverse(vector<int>& arr){
    int left = 0;
    int right = arr.size() - 1;
    while(left < right){
        swap(arr[left], arr[right]);
        left++;
        right--;
    }
}
vector<int> min_Max(vector<int>& arr){
    int min = arr[0];
    int max = arr[0];
    for(int i = 1; i < arr.size(); i++){
        if(arr[i] < min){
            min = arr[i];
        }
        if(arr[i] > max){
            max = arr[i];
        }
    }
    return {min, max};
}
int main(){
    vector<int> arr = {1, 2, 3, 4, 5};
    cout << find_k(arr, 3) << endl;
    reverse(arr);
    for(int i = 0; i < arr.size(); i++){
        cout << arr[i] << " ";
    }
    cout << endl;
    vector<int> result = min_Max(arr);
    cout << "Min: " << result[0] << " Max: " << result[1] << endl;
    return 0;
}