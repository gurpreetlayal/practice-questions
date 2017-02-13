/*
Given n, how many structurally unique BST's (binary search trees) that store values 1...n?

For example,
Given n = 3, there are a total of 5 unique BST's.

   1         3     3      2      1
    \       /     /      / \      \
     3     2     1      1   3      2
    /     /       \                 \
   2     1         2                 3

int numTrees(int n);

*/
#include <iostream>
#include <string>
//#include <stdlib.h>

using namespace std; 

int uniqueTree(int n) {

    if (n <= 2) {
        return n;
    }

    int t = 0;
    for (int i = 0; i < n; i++) {
        auto getLeft = uniqueTree(i);
        auto getRight = uniqueTree(n - 1 - i);
        (getLeft == 0) ? getLeft = 1: getLeft;
        (getRight == 0) ? getRight = 1: getRight;

        t += getLeft * getRight;
    }

    return t;
}

int uniqueTreeDP(int n, int* cache) {

    if (cache[n] > 0) {
        return cache[n];
    }
    if (n <= 2) {
        cache[n] = n;
        return cache[n];
    }

    int t = 0;
    for (int i = 0; i < n; i++) {
        auto getLeft = uniqueTreeDP(i, cache);
        auto getRight = uniqueTreeDP(n - 1 - i, cache);
        (getLeft == 0) ? getLeft = 1: getLeft;
        (getRight == 0) ? getRight = 1: getRight;

        t += getLeft * getRight;
    }
    cache[n] = t;

    return cache[n];
}

int numTrees(int n) {
    int cache[n + 1];
    for (int i = 0; i <= n; i++) cache[i] = 0;

    return uniqueTreeDP(n, cache);
}

int main(int argc, char* argv[]) {

    cout << numTrees(atoi(argv[1]));
    return 0;
}
