/*
Given two words word1 and word2, find the minimum number of steps required to convert word1 to word2. (each operation is counted as 1 step.)

You have the following 3 operations permitted on a word:

a) Insert a character
b) Delete a character
c) Replace a character

*/
#include <iostream>
#include <vector>
#include <climits>

using namespace std;

const int costOfReplace = 1;
const int costOfDelete = 1;
const int costOfInsert = 1;

void initTable(string word1, string word2, vector<vector<int>> table);
int minDistanceCore(string word1, int idx1, string word2, int idx2, vector<vector<int>> table);
int min(int x, int y, int z);


int minDistance(string word1, string word2) {
    if (word1.size() == 0 || word2.size() == 0) { return 0; }
    vector<vector<int>> table(word1.size(), vector<int>(word2.size(),INT_MAX));
    initTable(word1, word2, table);
    return minDistanceCore(word1, word1.size()-1, word2, word2.size()-1, table);
}

void initTable(string word1, string word2, vector<vector<int>> table) {
    if (*word1.begin() == *word2.begin()) {
        table[0][0] = 0;
    } else {
        table[0][0] = 1;
    }
    
    for (int i = 1; i < table[0].size(); ++i) {
        table[0][i] = table[0][i-1] + 1;
    }
    for (int i = 1; i < table.size(); ++i) {
        table[i][0] = table[i-1][0] + 1;
    }
}

int minDistanceCore(string word1, int idx1, string word2, int idx2, vector<vector<int>> table) {
    if (idx1 < 0 || idx2 < 0) {
        return INT_MAX;
    }
    
    if (table[idx1][idx2] < INT_MAX) {
        return table[idx1][idx2];
    }
    
    if (*(word1.begin() + idx1) == *(word2.begin() + idx2)) {
        table[idx1][idx2] = minDistanceCore(word1, idx1-1, word2, idx2-1, table);
        return table[idx1][idx2];
    }
    
    int rep = minDistanceCore(word1, idx1-1, word2, idx2-1, table);
    int del = minDistanceCore(word1, idx1, word2, idx2-1, table);
    int ins = minDistanceCore(word1, idx1-1, word2, idx2, table);
    
    if (rep < INT_MAX) { rep += costOfReplace; } else { rep = costOfReplace; }
    if (del < INT_MAX) { del += costOfDelete; } else { del = costOfDelete; }
    if (ins < INT_MAX) { ins += costOfInsert; } else { ins = costOfInsert; }
    
    table[idx1][idx2] = min(rep, del, ins);
    return table[idx1][idx2];
}

int min2(int x, int y) {
    if (x < y) { return x; }
    else { return y; }
}

int min(int x, int y, int z) {
    return min2(x, min2(y, z));
}

int main() {
    cout << minDistance("hodor", "door");
}
