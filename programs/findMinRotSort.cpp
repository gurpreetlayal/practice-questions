/*
Suppose a sorted array is rotated at some pivot unknown to you beforehand.

(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).

Find the minimum element.

You may assume no duplicate exists in the array.
*/

int main() {

}

int findMin(vector<int>& nums) {
    return findMinBinSearch(nums, 0, nums.size()-1);
}

int findMinBinSearch(vector<int>& nums, int b, int e) {
    if (b > e) {
        return INT_MIN;
    }

    int m = (b + e)/2;
    if (m == b || m == e) {
        return min(nums[b], nums[e]);
    }

    if (nums[b] < nums[m]) {
        if (nums[m] <= nums[e] return nums[0];
        else 
            return findMinBinSearch(nums, m, e);
    } else {
        return findMinBinSearch(nums, b, m);
    }
}
