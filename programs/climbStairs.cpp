#include <iostream>
#include <vector>

using namespace std;

int climbStairsCore(int n, vector<int>& cache); 

int climbStairs(int n) {
    vector<int> cache(n+1);
    cache[0] = cache[1] = 1;
    cache[2] = 2;
    for (auto& val: cache) { cout << val << endl; }
    auto result = climbStairsCore(n, cache);
    for (auto& val: cache) { cout << val << endl; }
    return result;
}

int climbStairsCore(int n, vector<int>& cache) {
    if (n < 0) { return 0; }
    if (cache[n]) { return cache[n]; }
    cache[n] = climbStairsCore(n-1, cache) + climbStairsCore(n-2, cache);
    return cache[n];
}

int main() {
    cout << climbStairs(10) << endl;
    
    return 0;
}
