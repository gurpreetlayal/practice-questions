
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


****

LC 240. Search a 2D Matrix II
Write an efficient algorithm that searches for a value in an m x n matrix. This matrix has the following properties:

Integers in each row are sorted in ascending from left to right.
Integers in each column are sorted in ascending from top to bottom.

EXACTLY SAME AS LC 74


MAIN IDEA: Code same as lc 74, but here it will take more of a step down approach, starting from c = N-1, everytime
checking if val < M[r][c] if so col-- otherwise row++;




****

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



****

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


****



// ================================
// DYNAMIC PROGRAMMING QUESTIONS
// ================================


L 70. Climbing Stairs

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




23. Merge k Sorted Lists
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



****

