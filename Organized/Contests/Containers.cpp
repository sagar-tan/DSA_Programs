#include <iostream>
using namespace std;

int maxContainers(int n, int w, int maxWeight) {
    int maxContainers = n * n; 
    int maxWeightContainers = maxWeight / w;
    return min(maxContainers, maxWeightContainers);
}

int main() {
    // Example test cases
    cout << maxContainers(2, 3, 15) << endl; // Output: 4
    cout << maxContainers(3, 5, 20) << endl; // Output: 4
    return 0;
}
