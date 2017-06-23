325. Maximum Size Subarray Sum Equals k
Given an array nums and a target value k, find the maximum length of a subarray that sums to k. If there isn't one, return 0 instead.

Note:
The sum of the entire nums array is guaranteed to fit within the 32-bit signed integer range.

Example 1:
Given nums = [1, -1, 5, -2, 3], k = 3,
return 4. (because the subarray [1, -1, 5, -2] sums to 3 and is the longest)

Example 2:
Given nums = [-2, -1, 2, 1], k = 1,
return 2. (because the subarray [-1, 2] sums to 1 and is the longest)

Follow Up:
Can you do it in O(n) time?

class Solution {
public:
    /* Main Idea: use map<sum, idx> storing partial sums.
        iterate through array summing the current idx value.
        if new sum = t, then max = idx+1 otherwise, if sum-t is in map
        then choose max of (cur idx - map idx , max).
        if sum value is not there in map, update value pair in map
    */
    int maxSubArrayLen(vector<int>& nums, int t) {
        unordered_map<int, int> kvmap;
        int sum = 0;
        int maxv = 0;
        for (int i = 0; i < nums.size(); i++) {
            sum += nums[i];
            if (sum == t) { maxv = i + 1; }
            else if (kvmap.find(sum-t) != kvmap.end()) {
                maxv = max (maxv, i - kvmap[sum-t]);
            }

            if (kvmap.find(sum) == kvmap.end()) kvmap[sum] = i;
        }
        return maxv;
    }
};




301. Remove Invalid Parentheses
Remove the minimum number of invalid parentheses in order to make the input string valid. Return all possible results.

Note: The input string may contain letters other than the parentheses ( and ).

Examples:
"()())()" -> ["()()()", "(())()"]
"(a)())()" -> ["(a)()()", "(a())()"]
")(" -> [""]


Main Idea: Use backtracking , everytime choosing to remove a parenthesis and
see if we reach till the end of string with all parenthesis balanced. since 
we want to make minium removals, everytime a minimum is seen, clear the result
2d vector. rest is regular backtracking.


vector<string> removeInvalidParentheses(string s) {
    vector<string> res;
    int idx = 0;
    removebt(s, idx, res);
    return res;
}

for (int i = 0; i < s.size(); i++) {
        if (isNotParenthesis(s[i])) { continue; }
        
        string news = s.substr(0, i);
        news.append(s.substr(i+1));
        
        removebt(news, idx, res);
    }




311. Sparse Matrix Multiplication

Given two sparse matrices A and B, return the result of AB.

You may assume that A's column number is equal to B's row number.

Example:

A = [
  [ 1, 0, 0],
  [-1, 0, 3]
]

B = [
  [ 7, 0, 0 ],
  [ 0, 0, 0 ],
  [ 0, 0, 1 ]
]


     |  1 0 0 |   | 7 0 0 |   |  7 0 0 |
AB = | -1 0 3 | x | 0 0 0 | = | -7 0 3 |
                  | 0 0 1 |
class Solution {
public:

    // create a res 2D vector<rowA,colB>
    // create a sparse 2D vector<rowA, pair<col-idx, val>> for input 2d vector A
    // fill sparseA.
    // for each value in sparseA, see what all values in B which can be multiplied
    // with sparseA[i].value and keep on storing the product result in resultant vector.
    vector<vector<int>> multiply(vector<vector<int>>& A, vector<vector<int>>& B) {
        const int rowA = A.size(), rowB = B.size();
        const int colA = A[0].size(), colB = B[0].size();
        
        // create res vector
        vector<vector<int>> res(rowA, vector<int>(colB, 0));
        vector<vector<pair<int, int>>> sparseA(rowA, vector<pair<int,int>>());
    
        for(int i = 0; i < rowA; i++)
           for(int j = 0; j < colA; j++) {
            if(A[i][j] != 0)  sparseA[i].emplace_back(j, A[i][j]);
         }
        for (int i = 0; i < rowA; ++i) 
         for (auto noZeros : sparseA[i]) 
          for (int j = 0; j < colB; ++j) {
              if(B[noZeros.first][j] != 0) res[i][j] += noZeros.second * B[noZeros.first][j];
        }
        return res;
    }
};



314. Binary Tree Vertical Order Traversal

Given a binary tree, return the vertical order traversal of its nodes' values. (ie, from top to bottom, column by column).

If two nodes are in the same row and column, the order should be from left to right.


Given binary tree [3,9,8,4,0,1,7,null,null,null,2,5] (0's right child is 2 and 1's left child is 5),
     3
    /\
   /  \
   9   8
  /\  /\
 /  \/  \
 4  01   7
    /\
   /  \
   5   2
return its vertical order traversal as:
[
  [4],
  [9,5],
  [3,0,1],
  [8,2],
  [7]
]

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    // Maintain result in a map<column, TreeNode*> and do a BFS.
    // each call to left subtree column-1 value, right subtree
    // column+1 value.
    vector<vector<int>> verticalOrder(TreeNode* root) {
        if (!root) { return vector<vector<int>>(); }
        
        vector<vector<int>> res;
        map<int, vector<int>> iMap;
        int level = 0;
        queue<pair<int, TreeNode*>> q;
        pair<int, TreeNode*> pairp(level, root);
        q.push(pairp);

        while(!q.empty()) {
            pair<int, TreeNode*> p = q.front();
            TreeNode* node = p.second;

            q.pop();
            // add node to approp. column index key.
            iMap[p.first].push_back(node->val);

            
            if (node->left) {
                q.push(pair<int, TreeNode*>(p.first-1, node->left));
            }

            if (node->right) {
                q.push(pair<int, TreeNode*>(p.first+1, node->right));
            }
        }

        for (auto c: iMap) {
            res.emplace_back(c.second.begin(), c.second.end());
        }
        return res;
    }
};





273. Integer to English Words
Convert a non-negative integer to its english words representation. Given input is guaranteed to be less than 231 - 1.

For example,
123 -> "One Hundred Twenty Three"
12345 -> "Twelve Thousand Three Hundred Forty Five"
1234567 -> "One Million Two Hundred Thirty Four Thousand Five Hundred Sixty Seven"
Hint:

Did you see a pattern in dividing the number into chunk of words? For example, 123 and 123000.
Group the number by thousands (3 digits). You can write a helper function that takes a number less than 1000 and convert just that chunk to words.
There are many edge cases. What are some good test cases? Does your code work with input such as 0? Or 1000010? (middle chunk is zero and should not be printed out)




Main Idea: create different sets for numbers < 20, set for tens etc. everytime, convert 1000 or less to bunch of words and move on to next chunk.

private final String[] LESS_THAN_20 = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
private final String[] TENS = {"", "Ten", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
private final String[] THOUSANDS = {"", "Thousand", "Million", "Billion"};

public String numberToWords(int num) {
    if (num == 0) return "Zero";

    int i = 0;
    String words = "";
    
    while (num > 0) {
        if (num % 1000 != 0)
            words = helper(num % 1000) +THOUSANDS[i] + " " + words;
        num /= 1000;
        i++;
    }
    
    return words.trim();
}

private String helper(int num) {
    if (num == 0)
        return "";
    else if (num < 20)
        return LESS_THAN_20[num] + " ";
    else if (num < 100)
        return TENS[num / 10] + " " + helper(num % 10);
    else
        return LESS_THAN_20[num / 100] + " Hundred " + helper(num % 100);
}






278. First Bad Version
Suppose you have n versions [1, 2, ..., n] and you want to find out the first bad one, which causes all the following ones to be bad.

You are given an API bool isBadVersion(version) which will return whether version is bad. Implement a function to find the first bad version. You should minimize the number of calls to the API.


// Main Idea: try to find out boundary such that, a[i] is bad and a[i-1] is not.
// that's the first bad version, use binary search to find

// Forward declaration of isBadVersion API.
bool isBadVersion(int version);

class Solution {
public:
    int firstBadVersion(int n) {
        return fbv(1, n);
    }
    
    int fbv(int s, int e) {
        if (s > e) { return 0; }
        
        int m = s + (e-s)/2;
        
        if (isBadVersion(m)) {
            if (m > 1) {
                if (!isBadVersion(m-1)) {
                    return m;
                }
            } else {
                return m;
            }
            
            return fbv(s, m-1);
        } else {
            return fbv(m+1, e);
        }
    }
};




17. Letter Combinations of a Phone Number
Given a digit string, return all possible letter combinations that the number could represent.

A mapping of digit to letters (just like on the telephone buttons)
Input:Digit string "23"
Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].


// Main Idea: Use backtracking, everytime choosing a number, for it, take 1 letter at a time,
//  remove that number from input, backtrack and so on





252. Meeting Rooms
Given an array of meeting time intervals consisting of start and end times [[s1,e1],[s2,e2],...] (si < ei), determine if a person could attend all meetings.

For example,
Given [[0, 30],[5, 10],[15, 20]],
return false.

/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
 
// Main Idea: Sort by meeting start times. then go thourgh the meetings
// list to see if there's any overlap between prev end and next meeting
// start time.
class Solution {
public:
    class compare {
    public:
        bool operator()(Interval i1, Interval i2) {
            return  (i1.start < i2.start);
        }
    };
    
    bool canAttendMeetings(vector<Interval>& intervals) {
        if (intervals.size() <= 1) { return true; }
        sort(intervals.begin(), intervals.end(), compare());
        
        for (int i = 0; i < intervals.size()-1; i++) {
            if (intervals[i].end > intervals[i+1].start) {
                return false;
            }
        }
        return true;
    }
};



253. Meeting Rooms II

Given an array of meeting time intervals consisting of start and end times [[s1,e1],[s2,e2],...] (si < ei), find the minimum number of conference rooms required.

For example,
Given [[0, 30],[5, 10],[15, 20]],
return 2.

/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
 
 // Main Idea: Maintain a map<meeting-time, how many meetings going on at this time>
 // for each start, increase value, in kv pair. for each end, decrease value in kv pair.
 // iterate through map and get a global max.
class Solution {
public:
    int minMeetingRooms(vector<Interval>& intervals) {
        map<int, int> ivmap;
        for (auto& iv : intervals) {
            ivmap[iv.start] += 1;
            ivmap[iv.end] -= 1;
        }
        
        int curmax = 0, gmax = 0;
        for (auto& iv : ivmap) {
            curmax += iv.second;
            gmax = max(gmax, curmax);
        }
        
        return gmax;
    }
};




91. Decode Ways
A message containing letters from A-Z is being encoded to numbers using the following mapping:

'A' -> 1
'B' -> 2
...
'Z' -> 26
Given an encoded message containing digits, determine the total number of ways to decode it.

For example,
Given encoded message "12", it could be decoded as "AB" (1 2) or "L" (12).

The number of ways decoding "12" is 2.


// Main Idea: Use DP. DP[n] = DP[n-1] if A[n] != 0 + DP[n-2] if A[N-1]A[N] is >=1 and <= 26
// copied from leetcode discussion.
public class Solution {
    public int numDecodings(String s) {
        if(s == null || s.length() == 0) {
            return 0;
        }
        int n = s.length();
        int[] dp = new int[n+1];
        dp[0] = 1;
        dp[1] = s.charAt(0) != '0' ? 1 : 0;
        for(int i = 2; i <= n; i++) {
            int first = Integer.valueOf(s.substring(i-1, i));
            int second = Integer.valueOf(s.substring(i-2, i));
            if(first >= 1 && first <= 9) {
               dp[i] += dp[i-1];  
            }
            if(second >= 10 && second <= 26) {
                dp[i] += dp[i-2];
            }
        }
        return dp[n];
    }


15. 3Sum
Given an array S of n integers, are there elements a, b, c in S such that a + b + c = 0? Find all unique triplets in the array which gives the sum of zero.

Note: The solution set must not contain duplicate triplets.

For example, given array S = [-1, 0, 1, 2, -1, -4],

A solution set is:
[
  [-1, 0, 1],
  [-1, -1, 2]
]

// Main idea: O(n2) solution, involves first sorting the array (o(nlogn)) and then fixing, i and moving j -> n and k->i



282. Expression Add Operators
Given a string that contains only digits 0-9 and a target value, return all possibilities to add binary operators (not unary) +, -, or * between the digits so they evaluate to the target value.

Examples: 
"123", 6 -> ["1+2+3", "1*2*3"] 
"232", 8 -> ["2*3+2", "2+3*2"]
"105", 5 -> ["1*0+5","10-5"]
"00", 0 -> ["0+0", "0-0", "0*0"]
"3456237490", 9191 -> []

// Main Idea: Use backtracking/DFS. everytime choose a operator(+,-,*), calculate the result, and move to next number.
// if finally reaches = target. store the expression. special handling for * operator since if previous operator is -
// then cur value will be changed. Below is the partial code
for (int i=pos+1; i<=num.size(); i++) {
    string t = num.substr(pos, i-pos);
    long now = stol(t);
    if (to_string(now).size() != t.size()) continue;
    dfs(res, num, target, cur+'+'+t, i, cv+now, now, '+');
    dfs(res, num, target, cur+'-'+t, i, cv-now, now, '-');
    dfs(res, num, target, cur+'*'+t, i, (op == '-') ? cv+pv - pv*now : ((op == '+') ? cv-pv + pv*now : pv*now), pv*now, op);
}

76. Minimum Window Substring
Main Idea: 2 pointers begin and end. 1 pointer pointing to next to begin(valid char w.r.t target). 1 hashmap to store target substring char occurences.

// My answer based on below leetcode solution

class Solution {
public:
    string minWindow(string s, string t) {
        vector<int> tmap(128,0);
        for (auto& c: t) { tmap[c]++; }

        int begin = 0, end = 0, d = INT_MAX, head = 0;
        int counter = t.size();

        while (end < s.size()) {
            if (tmap[s[end++]]-- > 0) counter--; // this char is in t
            print(tmap);
            while (counter == 0) {
                if ((end - begin) < d) {
                    d = end - begin;
                    head = begin;
                }
                if(tmap[s[begin++]]++ == 0)counter++;
            }
        }
        return (d == INT_MAX) ? "" : s.substr(head, d);
    }

    void print(vector<int> v) {
        for (int i = 0; i < v.size(); i++) { if (v[i] != 0 ) cout << "(" << i << "," << v[i] << ")"; }
        cout << endl;
    }
};

leetcode solution
string minWindow(string s, string t) {
        vector<int> map(128,0);
        for(auto c: t) map[c]++;
        int counter=t.size(), begin=0, end=0, d=INT_MAX, head=0;
        while(end<s.size()){
            if(map[s[end++]]-->0) counter--; //in t
            while(counter==0){ //valid
                if(end-begin<d)  d=end-(head=begin);
                if(map[s[begin++]]++==0) counter++;  //make it invalid
            }
        }
        return d==INT_MAX? "":s.substr(head, d);
    }

int findSubstring(string s){
        vector<int> map(128,0);
        int counter; // check whether the substring is valid
        int begin=0, end=0; //two pointers, one point to tail and one  head
        int d; //the length of substring

        for() { /* initialize the hash map here */ }

        while(end<s.size()){

            if(map[s[end++]]-- ?){  /* modify counter here */ }

            while(/* counter condition */){

                 /* update d here if finding minimum*/

                //increase begin to make it invalid/valid again

                if(map[s[begin++]]++ ?){ /*modify counter here*/ }
            }

            /* update d here if finding maximum*/
        }
        return d;
  }



157. Read N Characters Given Read4
The API: int read4(char *buf) reads 4 characters at a time from a file.

The return value is the actual number of characters read. For example, it returns 3 if there is only 3 characters left in the file.

By using the read4 API, implement the function int read(char *buf, int n) that reads n characters from the file.

Note:
The read function will only be called once for each test case.

class Solution {
public:
    /**
     * @param buf Destination buffer
     * @param n   Maximum number of characters to read
     * @return    The number of characters read
     */
    int read(char *buf, int n) {
        int r = read4(buf);
        int c = min(r, n);
        n = n - r;
        
        while(!(r < 4) && n > 0) {
            r = read4(buf+c);
            c += min(n,r);
            n -= r;
        }
        return c;
    }
};

285. Inorder Successor in BST

class Solution {
public:
    typedef TreeNode node;
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
        if (!root || !p) { return nullptr; }

        // if root->right there, then successor will definitely be
        // in right subtree.        
        if (p->right) {
            node* temp = p->right;
            while(temp->left) {
                temp = temp->left;
            }
            return temp;
        }
        
        // otherwise it'll be one of the parent/grandparent or above. find it.
        node* f = nullptr;
        findParent(root, p, &f);
        
        return f;
    }
    
    // main thing to remember, have to use bool as return type to set if, kid is
    // found. node** f holds the actual inorder successor node.
    bool findParent(node* root, node* p, node** f) {
        if (!root || !p) { return false; }
        
        if (root->left == p) {
            *f = root;
            return true;
        } else if (root->right == p) {
            return true;
        }
        
        if (p->val <= root->val) {
            auto t = findParent(root->left, p, f);
            if (t && !*f) {
                *f = root;
            }
            return t;
        } else {
            return findParent(root->right, p, f);
        }
    }





208. Implement Trie

Implement a trie with insert, search, and startsWith methods.

Note:
You may assume that all inputs are consist of lowercase letters a-z.

//Main Idea: the struct definition below

struct TrieNode {
    vector<TrieNode*> child;
    bool isLeaf;
    
    TrieNode() {
        child.resize(26, nullptr);
        isLeaf = false;
    }
    void reset() {
        for (int i = 0; i < child.size(); i++) {
            child[i] = nullptr;
        }
        isLeaf = false;
    }
};

class Trie {
    TrieNode* root;
}



211. Add and Search Word - Data structure design


//Main Idea: Basically use Trie to solve this problem.


341. Flatten Nested List Iterator

Given a nested list of integers, implement an iterator to flatten it.

Each element is either an integer, or a list -- whose elements may also be integers or other lists.

Example 1:
Given the list [[1,1],2,[1,1]],

By calling next repeatedly until hasNext returns false, the order of elements returned by next should be: [1,1,2,1,1].

Example 2:
Given the list [1,[4,[6]]],

By calling next repeatedly until hasNext returns false, the order of elements returned by next should be: [1,4,6].

public class NestedIterator implements Iterator<Integer> {
    Stack<NestedInteger> stack = new Stack<>();
    public NestedIterator(List<NestedInteger> nestedList) {
        for(int i = nestedList.size() - 1; i >= 0; i--) {
            stack.push(nestedList.get(i));
        }
    }

    @Override
    public Integer next() {
        return stack.pop().getInteger();
    }

    @Override
    public boolean hasNext() {
        while(!stack.isEmpty()) {
            NestedInteger curr = stack.peek();
            if(curr.isInteger()) {
                return true;
            }
            stack.pop();
            for(int i = curr.getList().size() - 1; i >= 0; i--) {
                stack.push(curr.getList().get(i));
            }
        }
        return false;
    }
}


75. Sort Colors
Given an array with n objects colored red, white or blue, sort them so that objects of the same color are adjacent, with the colors in the order red, white and blue.

Here, we will use the integers 0, 1, and 2 to represent the color red, white, and blue respectively.


class Solution {
public:
    void sortColors(vector<int>& A) {
        if (A.size() <= 0) {
            return;
        }
        int mid = 1;
        // start 3 pointers i j n.
        // i represents top of bottom array.
        // j represents currently inspected element, should be
        // somewhere in the middle array.
        // n represents bottom of top array.
        int i = 0, j = 0, n = A.size()-1;
        
        while (j <= n) {
            // case if: i -> first non red or first white element.[end of red array]
            // since j is less than mid, means j is red so swap i with j.
            // now j becomes white and i becomes red. do i++ so that
            // boundary of red element array is increased to handle newly added
            // element. move j, since now we inspect next element.
            if (A[j] < mid) {
                swap(A, i, j);
                i++;
                j++;
            } else if (A[j] > mid) {
                swap (A, j, n);
                n--;
            } else {
                j++;
            }
        }
    }
    
    void swap (vector<int>& A, int i, int j) {
        int temp = A[i];
        A[i] = A[j];
        A[j] = temp;
    }
};


43. Multiply large Strings of +ve integers
// Main Idea: res = r[sizeof a + sizeof b]
// int tempInt = (num1[i] - '0') * (num2[j] - '0') + (ans[i + j + 1] - '0') + carry;
// ans[i + j + 1] = '0' + tempInt % 10;
// carry = tempInt / 10;

class Solution {
public:
    string multiply(string num1, string num2) {
        string ans = string(num1.length() + num2.length(), '0');

        for (int i = num1.length() - 1; i >= 0; i--) {
            int carry = 0;
            for (int j = num2.length() - 1; j >= 0; j--) {
                int tempInt = (num1[i] - '0') * (num2[j] - '0') + (ans[i + j + 1] - '0') + carry;
                ans[i + j + 1] = '0' + tempInt % 10;
                carry = tempInt / 10;
            }
            ans[i] += carry;
        }

        size_t found = ans.find_first_not_of('0');
        if (found == string::npos) { return "0"; }
        return ans.substr(found);
    }

};
