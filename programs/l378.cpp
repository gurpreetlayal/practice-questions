/*
Given a n x n matrix where each of the rows and columns are sorted in ascending order, find the kth smallest element in the matrix.

Note that it is the kth smallest element in the sorted order, not the kth distinct element.

Example:

matrix = [
   [ 1,  5,  9],
   [10, 11, 13],
   [12, 13, 15]
],
k = 8,

return 13.

*/



#include "l.h"
/*
int kthsmallest(vector<vector<int>> v, int k) {
    int se = v[0][0];
    int ee = v[v.size()-1][v.size()-1];

    while (se < ee) {
        int mid = se + (ee-se)/2;

        int num = 0;
        for (int i = 0; i < v.size(); i++) {
            num += upper_bound(v.begin(), v.end(), mid) - v.begin();
        }
        if (num < k) {
            se = mid + 1;
        } else {
            ee = mid;
        }
   }
   return se;
}
*/

int main() {
    vector<int> v;
    v.push_back(1);
    v.push_back(2);
    cout << v.end() - v.begin();

    return 0;
}
