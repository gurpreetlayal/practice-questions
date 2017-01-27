
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

EXACTLY SAME AS 74


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


===========
LINKED LIST
===========


LC 160. Intersection of Two Linked Lists

Write a program to find the node at which the intersection of two singly linked lists begins.


For example, the following two linked lists:

A:          a1 → a2
                   ↘
                     c1 → c2 → c3
                   ↗            
B:     b1 → b2 → b3
begin to intersect at node c1.


Notes:

If the two linked lists have no intersection at all, return null.
The linked lists must retain their original structure after the function returns.
You may assume there are no cycles anywhere in the entire linked structure.
Your code should preferably run in O(n) time and use only O(1) memory.


/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if (headA == nullptr || headB == nullptr) { return nullptr; }
    
        int lenA = 0, lenB = 0;
        auto temp = headA;
        while (temp) {
            temp = temp->next;
            lenA++;
        }
    
        temp = headB;
        while (temp) {
            temp = temp->next;
            lenB++;
        }
    
        int offset = (lenA - lenB);
        if (lenA < lenB) {
            offset = lenB - lenA;
            temp = headB;
            while (offset) {
                temp = temp->next;
                offset--;
            }
            headB = temp;
        } else {
            temp = headA;
            while (offset) {
                temp = temp->next;
                offset--;
            }
            headA = temp;
        }
    
        while (headA && headB && headA->val != headB->val) {
            headA = headA->next;
            headB = headB->next;
        }
        return headA;
    }
};



***************************************************************************************************

LC 138. Copy List with Random Pointer

A linked list is given such that each node contains an additional random pointer which could point to any node in the list or null.

Return a deep copy of the list.

/**
 * Definition for singly-linked list with a random pointer.
 * struct RandomListNode {
 *     int label;
 *     RandomListNode *next, *random;
 *     RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
 * };
 */
class Solution {
public:
    typedef RandomListNode rnl;
    RandomListNode *copyRandomList(RandomListNode *head) {
        if (!head) {
            return head;
        }
        
        map<rnl*, int> olMap;
        map<int, rnl*> nlMap;
        
        int i = 1;
        auto temp = head;
        while (temp) {
            olMap[temp] = i++;
            temp = temp->next;
        }
        
        temp = head;
        
        i = 1;
        rnl *newHead = new rnl(temp->label);
        nlMap[i++] = newHead;
        auto prev = newHead;
        temp = temp->next;
        while(temp) {
            auto node = new rnl(temp->label);
            nlMap[i++] = node;
            prev->next = node;
            prev = node;
            temp = temp->next;
        }
        
        temp = head;
        auto node = newHead;
        while (temp && node) {
            node->random = nlMap[olMap[temp->random]];
            temp = temp->next;
            node = node->next;
        }
        
        return newHead;
    }
};



***************************************************************************************************

LC 445. Add Two Numbers II

You are given two non-empty linked lists representing two non-negative integers. The most significant digit comes first and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.

You may assume the two numbers do not contain any leading zero, except the number 0 itself.

Follow up:
What if you cannot modify the input lists? In other words, reversing the lists is not allowed.

Example:

Input: (7 -> 2 -> 4 -> 3) + (5 -> 6 -> 4)
Output: 7 -> 8 -> 0 -> 7



/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
       stack<int> s1, s2;
       
       if (l1 == nullptr || l2 == nullptr) { return nullptr; }
       
       while (l1) {
           s1.push(l1->val);
           l1 = l1->next;
       }
       
       while (l2) {
           s2.push(l2->val);
           l2 = l2->next;
       }
       
       ListNode* nextNode = nullptr;
       int c = 0;
       
       while (!s1.empty() && !s2.empty()) {
           ListNode* newNode = new ListNode((s1.top() + s2.top() + c) % 10);
           c = (s1.top() + s2.top() + c ) / 10;
           s1.pop();
           s2.pop();
           newNode->next = nextNode;
           nextNode = newNode;
       }
       
       while (!s1.empty()) {
           ListNode* newNode = new ListNode((s1.top() + c) % 10);
           c = (s1.top() + c) / 10;
           s1.pop();
           newNode->next = nextNode;
           nextNode = newNode;
       }

       while (!s2.empty()) {
           ListNode* newNode = new ListNode((s2.top() + c) % 10);
           c = (s2.top() + c) / 10;
           s2.pop();
           newNode->next = nextNode;
           nextNode = newNode;
       }

        if (c > 0) {
            ListNode* newNode = new ListNode(c);
            newNode->next = nextNode;
            nextNode = newNode;
        }
        return nextNode;
    }
};



***************************************************************************************************


LC 234. Palindrome Linked List 

Given a singly linked list, determine if it is a palindrome.

Follow up:
Could you do it in O(n) time and O(1) space?


/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    typedef ListNode node;
    bool isPalindrome(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return true;
        }
        node *n1, *n2;
        n1 = n2 = head;
        int num = 0;
        while (n2 != nullptr && n2->next != nullptr) {
            n1 = n1->next;
            n2 = n2->next;
            if (n2) n2 = n2->next;
        }
        
        auto n3 = head;
        if (n2 == nullptr) {
            auto n4 = n1;
            n4 = linkRev(n4);
            while (n3 != n1 && n4 != nullptr) {
                if (n3->val != n4->val) {
                    return false;
                }
                n3 = n3->next;
                n4 = n4->next;
            }
        } else if (n2->next == nullptr) {
            auto n4 = n1->next;
            n4 = linkRev(n4);
            while (n3 != n1 && n4 != nullptr) {
                if (n3->val != n4->val) {
                    return false;
                }
                n3 = n3->next;
                n4 = n4->next;
            }
        }
        return true;
    }
    
    node* linkRev(node* head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }
        
        auto t1 = head;
        auto t2 = head->next;
        
        t1->next = nullptr;

        while (t2) {
            
            auto t3 = t2->next;
            t2->next = t1;
            t1 = t2;
            t2 = t3;
        }
        
        return t1;
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


LC 25. Reverse Nodes in k-Group

Given a linked list, reverse the nodes of a linked list k at a time and return its modified list.

k is a positive integer and is less than or equal to the length of the linked list. If the number of nodes is not a multiple of k then left-out nodes in the end should remain as it is.

You may not alter the values in the nodes, only nodes itself may be changed.

Only constant memory is allowed.

For example,
Given this linked list: 1->2->3->4->5

For k = 2, you should return: 2->1->4->3->5

For k = 3, you should return: 3->2->1->4->5



/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    typedef ListNode node;
    ListNode* reverseKGroup(ListNode* head, int k) {
        stack<node*> stk;
        int curk = k;
        
        node* temp = head;
        node* newHead = nullptr;
        node* prevl = nullptr;
        while(temp) {
            while(temp && curk > 0) {
                stk.push(temp);
                temp = temp->next;
                curk--;
            }
            
            if (curk > 0 && temp == nullptr) {
                break;
            }

            if (!newHead) {
                newHead = stk.top();
            }
            
            while (!stk.empty()) {
                if (prevl) {
                    prevl->next = stk.top();
                    stk.pop();
                    prevl = prevl->next;
                } else {
                    prevl = stk.top();
                    stk.pop();
                }
            }
            prevl->next = temp;
            curk = k;
        }
        
        if (!newHead) {
            newHead = head;
        }
        
        return newHead;
    }
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

LC 46. Permutations

Given a collection of distinct numbers, return all possible permutations.

For example,
[1,2,3] have the following permutations:
[
  [1,2,3],
  [1,3,2],
  [2,1,3],
  [2,3,1],
  [3,1,2],
  [3,2,1]
]


class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        if (nums.size() == 0) {
            return vector<vector<int>>(0, vector<int>());
        }
        
        vector<int> onep;
        vector<vector<int>> res;
        permuteBackTracker(nums, onep, res);
        return res;
    }
    
    void permuteBackTracker(vector<int>& n, vector<int>& onep, vector<vector<int>>& res) {
        if (n.empty()) {
            res.push_back(onep);
            return;
        }
        
        for (int i = 0; i < n.size(); i++) {
            auto localonep = onep;
            onep.push_back(n[i]);
            auto temp = n;
            temp.erase(temp.begin() + i);
            permuteBackTracker(temp, onep, res);
            
            onep = localonep;
        }
    }
};


***************************************************************************************************


LC 79. Word Search

Given a 2D board and a word, find if the word exists in the grid.

The word can be constructed from letters of sequentially adjacent cell, where "adjacent" cells are those horizontally or vertically neighboring. The same letter cell may not be used more than once.

For example,
Given board =

[
  ['A','B','C','E'],
  ['S','F','C','S'],
  ['A','D','E','E']
]
word = "ABCCED", -> returns true,
word = "SEE", -> returns true,
word = "ABCB", -> returns false.

MAIN IDEA: Maintain a matrix for marking node as visited. Recursively chose amongst all 4(right,left,up,down) options(if option not marked visited) until end of search string.


bool exist(char** b, int r, int c, char* word) {
    bool** v = (bool**)malloc(sizeof(bool*)*r);
    for (int i = 0; i < r; i++) {
        v[i] = (bool*)malloc(sizeof(bool)*c);
    }
    resetVisited(v, r, c);
    bool res = false;

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            resetVisited(v, r, c);
            //cache
            char* cacheword = word;

            res |= search_board(b, r - 1, c - 1, i, j, word, v);
            if (res) { return res; }

            word = cacheword;
        }
    }
    return res;
}

bool search_board(char** b, int r, int c, int i, int j, char* word, bool** v) {

    bool res = false;
    if (*word == '\0') {
        return true;
    }
    
    if (i > r || i < 0 || j > c || j < 0) {
        return false;
    }

    if (*word != '\0' && *word == b[i][j] && v[i][j] == false) {
        v[i][j] = true;
        res |= (search_board(b, r, c, i, j - 1, word + 1, v) ||
                search_board(b, r, c, i, j + 1, word + 1, v) ||
                search_board(b, r, c, i - 1, j, word + 1, v) ||
                search_board(b, r, c, i + 1, j, word + 1, v));
        v[i][j] = false;
    }

    return res;
}

void resetVisited(bool** v, int r, int c) {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            v[i][j] = false;
        }
    }
}



***************************************************************************************************


LC 78. Subsets

Given a set of distinct integers, nums, return all possible subsets.

Note: The solution set must not contain duplicate subsets.

For example,
If nums = [1,2,3], a solution is:

[
  [3],
  [1],
  [2],
  [1,2,3],
  [1,3],
  [2,3],
  [1,2],
  []
]

class Solution {
public:
    typedef vector<vector<int>> v2d;
    typedef vector<int> v1d;
    vector<vector<int>> subsets(vector<int>& nums) {
        v2d res;
        v1d ones;
        
        subsetBackTracker(nums, ones, res);
        return res;
    }
    
    void subsetBackTracker(v1d& v, v1d& ones, v2d& res) {
        if (v.empty()) {
            res.push_back(ones);
            return;
        }
        
        auto cacheones = ones;
        auto cachev = v;
        
        v.erase(v.end() - 1);
        subsetBackTracker(v, ones, res);
        
        v = cachev;
        ones = cacheones;
        
        ones.push_back(*(v.end() - 1));
        v.erase(v.end() - 1);
        
        subsetBackTracker(v, ones, res);
    }
};



***************************************************************************************************


LC 131. Palindrome Partitioning

Given a string s, partition s such that every substring of the partition is a palindrome.

Return all possible palindrome partitioning of s.

For example, given s = "aab",
Return

[
  ["aa","b"],
  ["a","a","b"]
]

class Solution {
public:
    typedef vector<vector<string>> v2d;
    typedef vector<string> v1d;
    vector<vector<string>> partition(string s) {
        v2d res;
        v1d onep;
        string::iterator itr = s.begin();
        pBackTracker(s, itr, onep, res);
        return res;
    }
    
    void pBackTracker(string& s, string::iterator itrdx, v1d& onep, v2d& res) {
        if (itrdx == s.end()) {
            res.push_back(onep);
            return;
        }
        
        for (string::iterator itr = itrdx; itr != s.end(); itr++) {
            if (!isAnagram(s, itrdx, itr)) {
                continue;
            }
            auto cacheonep = onep;
            auto itrtemp = itr + 1;
            
            string temp(itrdx, itrtemp);
            onep.push_back(temp);

            pBackTracker(s, itrtemp, onep, res);

            onep = cacheonep;
        }
    }
    
    bool isAnagram(string& s, string::iterator i1, string::iterator i2) {
        while (i1 < i2) {
            if (*i1 != *i2) {
                return false;
            }
            i1++;
            i2--;
        }
        return true;
    }
    
};


***************************************************************************************************


LC 47. Permutations II

Given a collection of numbers that might contain duplicates, return all possible unique permutations.

For example,
[1,1,2] have the following unique permutations:
[
  [1,1,2],
  [1,2,1],
  [2,1,1]
]


class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        
        vector<int> oneP;
        vector<vector<int>> result;
        
        pBackTracker(nums, oneP, result);
        return result;
    }
    
    void pBackTracker(vector<int>& v, vector<int>& onep, vector<vector<int>>& res) {
        if (v.empty()) {
            res.push_back(onep);
            return;
        }
        
        set<int> seen;
        for (int i = 0; i < v.size(); i++) {
            if (seen.find(v[i]) != seen.end()) {
                continue;
            }
            
            seen.insert(v[i]);
            auto cacheonep = onep;
            auto cachev = v;
            
            onep.push_back(v[i]);
            v.erase(v.begin() + i);
            
            pBackTracker(v, onep, res);
            
            v = cachev;
            onep = cacheonep;
        }
    }
};



***************************************************************************************************


================
ARRAY
================


LC 215. Kth Largest Element in an Array

Find the kth largest element in an unsorted array. Note that it is the kth largest element in the sorted order, not the kth distinct element.

For example,
Given [3,2,1,5,6,4] and k = 2, return 5.

Note: 
You may assume k is always valid, 1 ≤ k ≤ array's length.


MAIN IDEA:
2 ways:
1st : Headp based solution. Maintain a min heap of size k, and for all elements (k+1 -> n), pop min element and push the new element in the heap.
2nd : Quick select algorithm, choose mid/randomly a value as pivot and move all elements < pivot to left and all elements > pivot to right. and so on.

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        if (nums.size() == 0 || k <= 0 || nums.size() < k) {
            return -1;
        }
        
        multiset<int> s;
        vector<int>::iterator itr = nums.begin();
        while((itr - nums.begin()) < k) {
            s.insert(*itr);
            itr++;
        }
        
        multiset<int>::iterator kmax = min_element(s.begin(), s.end());
        
        while (itr != nums.end()) {
            if (*itr > *kmax) {
                s.erase(kmax);
                s.insert(*itr);
                kmax = min_element(s.begin(), s.end());
            }
            itr++;
        }
        
        return *kmax;
    }
};



***************************************************************************************************

=======================
GENERIC ARRAY QUESTIONS
=======================


LC 339. Nested List Weight Sum

Given a nested list of integers, return the sum of all integers in the list weighted by their depth.

Each element is either an integer, or a list -- whose elements may also be integers or other lists.

Example 1:
Given the list [[1,1],2,[1,1]], return 10. (four 1's at depth 2, one 2 at depth 1)

Example 2:
Given the list [1,[4,[6]]], return 27. (one 1 at depth 1, one 4 at depth 2, and one 6 at depth 3; 1 + 4*2 + 6*3 = 27)


MAIN IDEA:
Inspect each element at a time, starting from last or starting from first.
    If int, then sum = intval*current_depth + recursive(remaining array - intval)
    If list, then sum = recursive(list, current_depth + 1) + recursive(remaining array - list)


/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */
class Solution {
public:
    int depthSum(vector<NestedInteger>& nestedList) {
        int depth = 1;
        return depthSum(nestedList, depth);
    }
    
    int depthSum(vector<NestedInteger>& nestedList, int depth) {
        if (nestedList.empty()) {
            return 0;
        }
        int local_sum = 0;
        if (nestedList[nestedList.size()-1].isInteger()) {
            local_sum = nestedList[nestedList.size()-1].getInteger() * depth;
        } else {
            auto list = nestedList[nestedList.size()-1].getList();
            vector<NestedInteger> vlast(list.begin(), list.end());
            local_sum = depthSum(vlast, depth + 1);
        }
        nestedList.erase(nestedList.end()-1);
        return local_sum + depthSum(nestedList,depth);
    }
};


***************************************************************************************************



