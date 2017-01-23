
****

LC 74. Search a 2D Matrix

Write an efficient algorithm that searches for a value in an m x n matrix.
This matrix has the following properties:

Integers in each row are sorted from left to right.
The first integer of each row is greater than the last integer of the previous row.



class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if (matrix.size() == 0) {
            return false;
        }
        int r = 0;
        if (matrix[0].size() == 0) {
            return false;
        }
        int c = matrix[0].size()-1;
        
        // start from v: [0][c-1] -> [n-1][c-1]
        // check for target < v. Then do a binary
        // search of target in vector [x][0->c-1]
        while((r <= matrix.size()-1) && (c >= 0)) {
            if (target == matrix[r][c]) {
                return true;
            } else if (target < matrix[r][c]) {
                c--;
            } else {
                r++;
            }
        }
        return false;
    }
};


***************************************************************************************************

LC 240. Search a 2D Matrix II
Write an efficient algorithm that searches for a value in an m x n matrix. This matrix has the following properties:

Integers in each row are sorted in ascending from left to right.
Integers in each column are sorted in ascending from top to bottom.

EXACTLY SAME AS LC 74


MAIN IDEA: Code same as lc 74, but here it will take more of a step down approach, starting from c = N-1, everytime
checking if val < M[r][c] if so col-- otherwise row++;




***************************************************************************************************

LC 54. Spiral Matrix
Given a matrix of m x n elements (m rows, n columns), return all elements of the matrix in spiral order.

MAIN IDEA: Code is simple enough. Just look at that.

vector<int> spiralOrder(vector<vector<int>>& m) {
        int sr = 0, er = m.size()-1;
        int sc = 0, ec = 0;
        if (m.size()) {
            ec = m[0].size()-1;
        }
        vector<int> res;
        while ((sr <= er) && (sc <= ec)) {
            for (int i = sc; i <= ec; i++) {
                res.push_back(m[sr][i]);
            }
            sr++;
            if (sr > er) { break; }
            for(int i = sr; i <= er; i++) {
                res.push_back(m[i][ec]);
            }
            ec--;
            if(ec < sc) { break; }
            for (int i = ec; i >= sc; i--) {
                res.push_back(m[er][i]);
            }
            er--;
            if (er < sr) { break; }
            for (int i = er; i >= sr; i--) {
                res.push_back(m[i][sc]);
            }
            sc++;
        }
        return res;
    }



***************************************************************************************************

LC 378. Kth Smallest Element in a Sorted Matrix
Given a n x n matrix where each of the rows and columns are sorted in ascending order, find the kth smallest element in the matrix.

Note that it is the kth smallest element in the sorted order, not the kth distinct element.

class Solution {
public:
    int kthSmallest(vector<vector<int>>& m, int k) {
        int se = m[0][0];
        int ee = m[m.size()-1][m.size()-1];

        // start from [0][0] -> [n-1][n-1] : binary search space
        // calculate number of elements which are less that mid value.
        // if > k, then reduce the search space as start value -> mid
        // otherwise search between mid + 1 -> end value.
        while(se < ee) {
            int mid = se + (ee - se)/2;
            int num = 0;
            for (int i = 0; i < m.size(); i++) {
                // calculate number of elements smaller than mid.
                // lets say 3 elements are less than mid, so this api will
                // return 3. (0,1,2,3) [3] being mid, but here because 0 is overlooked
                // so whatever upper_bound returns can be said returns number of numbers
                // less than mid.
                num += (upper_bound(m[i].begin(), m[i].end(), mid) - m[i].begin());
            }
            
            if (num < k) {
                se = mid + 1;
            } else {
                ee = mid;
            }
        }
        
        return se;
    }
};


***************************************************************************************************



// ================================
// DYNAMIC PROGRAMMING QUESTIONS
// ================================


LC 70. Climbing Stairs

You are climbing a stair case. It takes n steps to reach to the top.

Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?

Note: Given n will be a positive integer.



MAIN IDEA: Fibonacci series.

DP[n] = DP[n-1] + DP[n-2]


class Solution {
public:
    int climbStairs(int n) {
        vector<int> cache(n+1);
        cache[0] = cache[1] = 1;
        cache[2] = 2;
        return climbStairsCore(n, cache);
    }
    
    int climbStairsCore(int n, vector<int>& cache) {
        if (n < 0) { return 0; }
        if (cache[n]) { return cache[n]; }
        cache[n] = climbStairsCore(n-1, cache) + climbStairsCore(n-2, cache);
        return cache[n];
    }
};



***************************************************************************************************


LC 198. House Robber

You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed, the only constraint stopping you from robbing each of them is that adjacent houses have security system connected and it will automatically contact the police if two adjacent houses were broken into on the same night.

Given a list of non-negative integers representing the amount of money of each house, determine the maximum amount of money you can rob tonight without alerting the police.



MAIN IDEA:
At any i, choose either to pick or not pick vi. Take the max out of it.

DP EQUATION:

DP[i] = max(DP[i-1], v[i] + DP[i-2])


class Solution {
public:
    int rob(vector<int>& nums) {
        vector<int> cache(nums.size()+1, 0);
        
        int max_i_2 = 0;
        for (int i = 1; i <= nums.size(); i++) {
            cache[i] = max(nums[i-1] + max_i_2, cache[i-1]);
            if (max_i_2 < cache[i-1]) {
                max_i_2 = cache[i-1];
            }
        }
        return cache[nums.size()];
    }
};

***************************************************************************************************


LC 53. Maximum Subarray

Find the contiguous subarray within an array (containing at least one number) which has the largest sum.

For example, given the array [-2,1,-3,4,-1,2,1,-5,4],
the contiguous subarray [4,-1,2,1] has the largest sum = 6.


2 Solutions. 1 with DP, 2nd using kadane's algorithm

DP Solution
===========
MAIN IDEA: At every i, pick max(num[i], max seen until i-1, max which includes i-1 value as well + num[i])

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        if (nums.empty()) {
            return -1;
        }
        int m_at_i = nums[0];
        int m_till_i = nums[0];
        
        for (int i = 1; i < nums.size(); i++) {
            m_at_i = max(nums[i], m_at_i + nums[i]);
            m_till_i = max(m_at_i, m_till_i);
        }
        
        return m_till_i;
    }
};


Kadane Algorithm
================
MAIN IDEA: starting from i = 0, keep on adding numbers. If the sum becomes negative, reject that whole set.
Also, everytime you add a num[i] maintain a global max. Return global max at the end.


int maxSubArray(int* a, int n) {
  if (a == NULL || n <= 0) {
      return 0;
  }
  
  int s = 0, e = 0;
  return kadane(a, n, &s, &e);
}

int kadane(int *a, int n, int* s, int* e) {
    int cm = a[0], cms = 0, cme = 0;
    int m = a[0];
    
    for (int i = 1; i < n; i++) {
        if (cm < 0) {
            cm = 0;
            cms = i;
        }
        
        cm += a[i];
        cme = i;
        
        if (cm > m) {
            m = cm;
            *s = cms;
            *e = cme;
        }
    }
    return m;
}


***************************************************************************************************

LC 338. Counting Bits

Given a non negative integer number num. For every numbers i in the range 0 ≤ i ≤ num calculate the number of 1's in their binary representation and return them as an array.

Example:
For num = 5 you should return [0,1,1,2,1,2].

Follow up:

It is very easy to come up with a solution with run time O(n*sizeof(integer)). But can you do it in linear time O(n) /possibly in a single pass?
Space complexity should be O(n).
Can you do it like a boss? Do it without using any builtin function like __builtin_popcount in c++ or in any other language.


MAIN IDEA:
For every number,
if number is even then it will have same number of 1's in its binary representation as has number/2
if odd then it will have 1 + number of bits in number/2


class Solution {
public:
    vector<int> countBits(int num) {
        if (num <= 0) {
            return vector<int>(1,0);
        }
        vector<int> cache(num+1);
        cache[0] = 0;
        cache[1] = 1;
        for (int i = 2; i <= num; i++) {
            if (i%2) {
                cache[i] = 1 + cache[i/2];
            } else {
                cache[i] = cache[i/2];
            }
        }
        
        return cache;
    }
};


***************************************************************************************************

LC 139. Word Break

Given a non-empty string s and a dictionary wordDict containing a list of non-empty words, determine if s can be segmented into a space-separated sequence of one or more dictionary words. You may assume the dictionary does not contain duplicate words.

For example, given
s = "leetcode",
dict = ["leet", "code"].

Return true because "leetcode" can be segmented as "leet code".


MAIN IDEA:
Basically look for all substrings ending at i starting from 0->i-1. See if they are in dictionary, if they are then the result at i will be equal to result that was at cache[j].

DP[i] = DP[j] for all j: 0 ->i-1 if (substr(j,i) is in dictionary)

public:
    bool wordBreak(string s, unordered_set<string>& dict) {
        vector<bool> cache(s.size() + 1, false);
        cache[0] = true;
        
        for (int i = 1; i <= s.size(); i++) {
            for (int j = 1; j <= i; j++) {
                auto subst = s.substr(j - 1, i - j + 1);
                if (dict.find(subst) != dict.end()) {
                    cache[i] = cache[j - 1];
                }
                if (cache[i]) {
                    break;
                }
            }
        }
        return cache[s.size()];
    }
};



***************************************************************************************************


LC 152. Maximum Product Subarray

Find the contiguous subarray within an array (containing at least one number) which has the largest product.

For example, given the array [2,3,-2,4],
the contiguous subarray [2,3] has the largest product = 6.


MAIN IDEA:
Since the numbers can be negative as well and -num2*-num1 is positive, so at every i we calculate
max as well as min, since this min could become max if next i is -ve. So at every i we calculate
max according to dp equation below:

DP[i] = max (max_at_i-1*num[i], min_at_i-1*num[i], num[i])
and keep a global_max, keep it updated with every inspection of number i:0->n-1


class Solution {
public:
    int maxProduct(vector<int>& nums) {
       
        
        int max_at_i_minus_1 = nums[0];
        int max_till_i_minus_1 = nums[0];
        int min_at_i_minus_1 = nums[0];
        
        for (int i = 1; i < nums.size(); i++) {
           auto max_at_i = max(max(max_at_i_minus_1*nums[i],min_at_i_minus_1*nums[i]), nums[i]);
           auto min_at_i = min(min(max_at_i_minus_1*nums[i],min_at_i_minus_1*nums[i]), nums[i]);
           if (max_at_i > max_till_i_minus_1) max_till_i_minus_1 = max_at_i;
           max_at_i_minus_1 = max_at_i;
           min_at_i_minus_1 = min_at_i;
        }
        return max_till_i_minus_1;
    }
    
    void print(vector<int> v) {
        for (auto& c : v) {
            cout << c << " ";
        }
        cout <<endl;
    }
};


***************************************************************************************************

LC 96. Unique Binary Search Trees

Given n, how many structurally unique BST's (binary search trees) that store values 1...n?

For example,
Given n = 3, there are a total of 5 unique BST's.

   1         3     3      2      1
    \       /     /      / \      \
     3     2     1      1   3      2
    /     /       \                 \
   2     1         2                 3


MAIN IDEA: For a given n, we can choose left subtree varying from (0 -> n) where are right subtree varying from (n -> 0).
Total subtrees will then be leftsubtreecount*rightsubtreecount.

class Solution {
public:
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
};


***************************************************************************************************

LC 62. Unique Paths

A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).

The robot can only move either down or right at any point in time. The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below).

How many possible unique paths are there?


MAIN IDEA : 
DP[i][j] = DP[i-1][j] + DP[i][j-1]

class Solution {
public:
    int uniquePaths(int m, int n) {
        int** cache = new int*[m];
        for (int i = 0; i < m; i++) {
            cache[i] = new int[n];
        }
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                cache[i][j] = 0;
        return uniquePathsCore(cache, m-1, n-1);
    }
    
    int uniquePathsCore(int** cache, int m, int n) {
        if (m < 0 || n < 0) {
            return 0;
        }
        
        if (cache[m][n] > 0) {
            return cache[m][n];
        }
        
        if (m == 0 && n == 0) {
            cache[m][n] = 1;
            return cache[m][n];
        }
        
        cache[m][n] = (uniquePathsCore(cache, m-1, n) + uniquePathsCore(cache, m, n-1));
        return cache[m][n];
    }
};


***************************************************************************************************

LC 64. Minimum Path Sum

Given a m x n grid filled with non-negative numbers, find a path from top left to bottom right which minimizes the sum of all numbers along its path.

Note: You can only move either down or right at any point in time.


MAIN IDEA : 
DP[i][j] = val[i][j] + min (DP[i-1][j],DP[i][j-1])


class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        if (grid.empty()) {
            return 0;
        }
        int row = grid.size();
        int col = grid[0].size();
        vector<vector<int>> cache(row+1, vector<int>(col+1, INT_MAX));
        
        for (int i = 1; i <= row; i++) {
            for (int j = 1; j <= col; j++) {
                auto minval = min(cache[i-1][j], cache[i][j-1]);
                (minval == INT_MAX) ? minval = 0 : minval;
                cache[i][j] = grid[i-1][j-1] + minval;
            }
        }
        return cache[row][col];
    }
};

***************************************************************************************************

LC 322. Coin Change

You are given coins of different denominations and a total amount of money amount. Write a function to compute the fewest number of coins that you need to make up that amount. If that amount of money cannot be made up by any combination of the coins, return -1.

Example 1:
coins = [1, 2, 5], amount = 11
return 3 (11 = 5 + 5 + 1)

Example 2:
coins = [2], amount = 3
return -1.

Note:
You may assume that you have an infinite number of each kind of coin.


MAIN IDEA: Pseudo polynomial time, it's a subset sum problem with repetitions or a knapsack problem with unlimited number of all items.
run time O(n.|S|) where n is number of items and |S| is length of input, here it's the amount.

DP[target] = min(1+DP[target-vi]) for all i numbers v[0->n-1]

class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        vector<int> cache(amount+1, amount+1);
        
        cache[0] = 0;
        for (int t = 1; t <= amount; t++) {
            for (int num = 0; num < coins.size(); num++) {
                if (coins[num] <= t) {
                    cache[t] = min(cache[t], 1+cache[t-coins[num]]);
                }
            }
        }
        
        if (cache[amount] > amount) { return -1; } else return cache[amount];
    }
    
};



***************************************************************************************************

LC 23. Merge k Sorted Lists
Merge k sorted linked lists and return it as one sorted list. Analyze and describe its complexity.

class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.empty()) {
            return nullptr;
        }
        ListNode* head = nullptr;
        priority_queue<ListNode*, vector<ListNode*>, Compare> pq;
        for (auto list: lists) {
            if (list) pq.push(list);
        }
        
        if (pq.empty()) {
            return nullptr;
        }
        head = pq.top();
        ListNode* prev = nullptr;
        while(!pq.empty()) {
            auto top = pq.top();
            pq.pop();
            if (top->next) {
                pq.push(top->next);
            }
            if (prev) { prev->next = top; }
            prev = top;
        }
        return head;
    }
    
    class Compare {
    public:
        bool operator()(ListNode* n1, ListNode* n2) {
            if (n1->val > n2->val) {
                return true;
            } else {
                return false;
            }
        }
    };
};


***************************************************************************************************

==========================================
BEST TIME TO BUY AND SELL STOCKS QUESTIONS
==========================================


VERSION 1: A DP Solution
=========

LC 121. Best Time to Buy and Sell Stock

Say you have an array for which the ith element is the price of a given stock on day i.

If you were only permitted to complete at most one transaction (ie, buy one and sell one share of the stock), design an algorithm to find the maximum profit.

Example 1:
Input: [7, 1, 5, 3, 6, 4]
Output: 5

max. difference = 6-1 = 5 (not 7-1 = 6, as selling price needs to be larger than buying price)
Example 2:
Input: [7, 6, 4, 3, 1]
Output: 0

In this case, no transaction is done, i.e. max profit = 0.


MAIN IDEA: Make a cache of size n
Each cache entry is max profit if the stock was sold on that day lets say day i and was purchased on minimum value day in between (0 - i-1) days.

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.size() <= 0) {
            return 0;
        }
        int cache[prices.size()];
        int min_i = prices[0];
        int pmax = INT_MIN;
        
        for (int i = 0; i < prices.size(); i++) {
            cache[i] = max(0, prices[i] - min_i);
            if (min_i > prices[i]) {
                min_i = prices[i];
            }
            if (pmax < cache[i]) {
                pmax = cache[i];
            }
        }
        
        return pmax;
    }
};



VERSION 2: A greedy solution
=========


LC 122. Best Time to Buy and Sell Stock II

Say you have an array for which the ith element is the price of a given stock on day i.

Design an algorithm to find the maximum profit. You may complete as many transactions as you like (ie, buy one and sell one share of the stock multiple times). However, you may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).


MAIN IDEA: Greedy approach. Where starting from day 0, keep on adding to profit such that day i+1 value > day i

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.size() <= 1) {
            return 0;
        }
        
        int profit = 0;
        for (int i = 1; i < prices.size(); i++) {
            if (prices[i] > prices[i-1]) {
                profit += (prices[i] - prices[i-1]);
            }
        }
    
        return profit;
    }
    
};


VERSION 3:
=========

LC 309. Best Time to Buy and Sell Stock with Cooldown

Say you have an array for which the ith element is the price of a given stock on day i.

Design an algorithm to find the maximum profit. You may complete as many transactions as you like (ie, buy one and sell one share of the stock multiple times) with the following restrictions:

You may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).
After you sell your stock, you cannot buy stock on next day. (ie, cooldown 1 day)
Example:

prices = [1, 2, 3, 0, 2]
maxProfit = 3
transactions = [buy, sell, cooldown, buy, sell]


MAIN IDEA: In comments below


class Solution {
public:
    int maxProfit(vector<int>& v) {
        int has1_sell;
        int has1_donothing;
        int has0_buy;
        int has0_donothing;
    
        if (v.size() < 2) {
            return 0;
        }
        // On every day i can take 1 of these above 4 decisions. The profit will be max of
        // doing these activities up until and including the last day.
    
        // for day 0, init these paths;
    
        has1_sell = 0; // because it's not possible to sell on 1st day.
        has1_donothing = -v[0]; // because on day 2, to have this option valid it means that stock was acquired earlier. That's why acquire price of day 1 is added.
        has0_buy = -v[0]; // cost of acquiring the stock on day 1.
        has0_donothing = 0; // profit will be 0 since no order executed.
    
        for (int i = 1; i < v.size(); i++) {
            auto lhas0_buy = -v[i] + has0_donothing;
            auto lhas0_donothing = max(has0_donothing, has1_sell);
            auto lhas1_sell = v[i] + max(has1_donothing, has0_buy);
            auto lhas1_donothing = max(has1_donothing, has0_buy);
            
            has1_sell = lhas1_sell;
            has1_donothing = lhas1_donothing;
            has0_buy = lhas0_buy;
            has0_donothing = lhas0_donothing;
        }
        return max(has1_sell, has0_donothing);
    }
};


***************************************************************************************************



===========================
BACKTRACKING
===========================



