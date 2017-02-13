/*
349. Intersection of Two Arrays

Given two arrays, write a function to compute their intersection.

Example:
Given nums1 = [1, 2, 2, 1], nums2 = [2, 2], return [2].

Note:
Each element in the result must be unique.
The result can be in any order.

vector<int> intersection(vector<int>& nums1, vector<int>& nums2);

*/
#include <iostream>
#include <vector>
#include <map>

using namespace std;

vector<int> intersection(vector<int>& nums1, vector<int>& nums2);

int main() {
    vector<int> v1 = {1,2,3,4};
    vector<int> v2 = {2,4,5};
    auto v = intersection(v1, v2);
    for (auto& val: v) {
        cout << val << " ";
    }
    return 0;
}

vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
    vector<int> res;
    map<int,int> imap;

    for (auto& v: nums1) {
        imap[v] = 1;
    }

    for (auto& v: nums2) {
        if (imap[v] == 1) {
            imap[v] = 2;
            res.push_back(v);
        }
    }
    return res;
}
