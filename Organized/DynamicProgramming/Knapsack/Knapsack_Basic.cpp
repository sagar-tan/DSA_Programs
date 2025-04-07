//0/1 KnapSack problem - Basic implementation
#include<iostream>
#include<vector>
using namespace std;

// Recursive knapsack function
int knapsack(vector<int>& weight, vector<int>& profit, int capacity, int index) {
    // Base cases
    if (index == 0) {
        if (weight[0] <= capacity) {
            return profit[0];
        }
        return 0;
    }
    
    // Don't include current item
    int notTake = knapsack(weight, profit, capacity, index-1);
    
    // Include current item if possible
    int take = 0;
    if (weight[index] <= capacity) {
        take = profit[index] + knapsack(weight, profit, capacity - weight[index], index-1);
    }
    
    // Return maximum of both choices
    return max(take, notTake);
}

int main() {
    int n = 3; // Number of items
    int capacity = 5; // Knapsack capacity
    
    vector<int> weight = {2, 1, 3}; // Weights of items
    vector<int> profit = {4, 2, 3}; // Profits of items
    
    cout << "Maximum profit: " << knapsack(weight, profit, capacity, n-1) << endl;
    
    return 0;
} 