/*
Given an array S of n integers, find three integers in S such that the sum is closest to a given number, target. Return the sum of the three integers. You may assume that each input would have exactly one solution.

    For example, given array S = {-1 2 1 -4}, and target = 1.

    The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).

    int threeSumClosest(vector<int>& nums, int target);
*/
#include<algorithm>
using namespace std;

int main () { }

int threeSumClosest(vector<int> nums, int target) {
    if (nums.size() < 3) {
        return 0;
    }

    int soln = INT_MAX;
    sort(nums.begin(), nums.end());

    for (int i = 0; i < nums.size(); ++i) {
        j = i+1;
        k = nums.size()-1;

        while (j < k) {
            if (abs(nums[i] + nums[j] + nums[k] - target) < abs(sol - target)) {
                 soln = nums[i] + nums[j] + nums[k];
            }

            if ((nums[i] + nums[j] + nums[k] - target) < 0) {
                ++j;
            } else if ((nums[i] + nums[j] + nums[k] - target) > 0) {
                --k;
            } else {
                return (nums[i] + nums[j] + nums[k]);
            }
        }
    }
    return soln;
}
