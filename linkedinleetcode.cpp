———
Linkedin

339. Nested List Weight Sum
Main Idea: 
Inspect each element, starting from end. 
if int then return (int*depth + foo(list-inspected element)) otherwise
if element is list, return (foo(sublist, depth+1) + foo(list-inspected element, depth)



243. Shortest Word Distance
243. Shortest Word Distance

Main Idea: Make hash-map<string,vector<int>> : string -> word[i]. vector<int> indexes where all word[i] (can be duplicate entries in input) appears.
Then for input (string a, string b), go though vector<int> for both and figure out min distance b/w all occurences of string a and string b.

156. Binary Tree Upside Down
Main Idea: Look code, it's simple.

    TreeNode* upsideDownBinaryTree(TreeNode* root) {
        if (!root || !root->left) { return root; }
        
        TreeNode* newRoot = upsideDownBinaryTree(root->left);
        
        root->left->left = root->right;
        root->left->right = root;
        
        root->left = nullptr;
        root->right = nullptr;
        return newRoot;
    }


256. Paint House
Main Idea: DP

DP[i] = min (cost[i][0], cost[i][1], cost[i][2]) where cost[i][0] = cost[i][0](actual cost of painting house i with paint type 0) + min(cost[i-1][1], cost[i-1][2]) and so on.

        for (int i = 1; i < costs.size(); i++) {
            int prevcostfor_i0 = min(costs[i-1][1], costs[i-1][2]);
            int prevcostfor_i1 = min(costs[i-1][0], costs[i-1][2]);
            int prevcostfor_i2 = min(costs[i-1][1], costs[i-1][0]);

            costs[i][0] = prevcostfor_i0 + costs[i][0];
            costs[i][1] = prevcostfor_i1 + costs[i][1];
            costs[i][2] = prevcostfor_i2 + costs[i][2];
        }
        return min(min(costs[costs.size()-1][0], costs[costs.size()-1][1]), costs[costs.size()-1][2]);


254. Factor Combinations
Main Idea: Back tracking/DFS. for each call pick a number from (2->n/2) and recursively call for foo(n/2). push cur -> result if n == 0



205. Isomorphic Strings
Main Idea: take 2 arrays each representing character range. loop over both strings and for every pair s1i and s2i, see if number of times they have occured till now is same.if not then some other character has been represented by this char in s1i , return false. otherwise just update the arrays[s1i] with current i value, because the order needs to be preserved. otherwise if order doesn't need to be preserved then in that case += 1 is enough.

        vector<int> arr1(256,0);
        vector<int> arr2(256,0);
        for (int i = 0; i < s.size(); i++) {
            if (arr1[s[i]] != arr2[t[i]]) {
                    return false;
            }
            arr1[s[i]] = i+1;
            arr2[t[i]] = i+1;
        }
        return true;
    }



53. Maximum Subarray
Main Idea: DP or kadane's algo.


50. Implement Pow(x,n)
Main Idea: Catch, n can be +ve or -ve. Recursively calculate pow for n/2 and then use that value. 
    double myPow(double x, int n) {
        if (n == 0) { return 1; }
        if (abs(n) == 1) {
            return (n >= 0) ? x : 1/x;
        }
        
        double halfRes = myPow(x, n/2);
        halfRes *= halfRes;
        return (n%2) ? ((n >= 0) ? x*halfRes : (1/x)*halfRes) : halfRes;
    }

297. Serialize and Deserialize Binary Tree
Main Idea: Do a pre order traversal of the tree. Push root->val to string then serialize root->left followed by root->right. For deserialize do it for first node and then it's children.



56. Merge Intervals

Main Idea: Is to follow idea of merge sort. divide it in 2 halves, run the main algo on those and then merge these already exclusive set of intervals. 
M(0, n) : run for M(0, n/2) , M(n/2+1, n) and then merge both results. keep pushing the intervals in a separate vector passed by argument to the main function.

57. Insert Interval
Main Idea: Figure out where to insert the interval. Using binary search. or as in leetcode solution O(n) just do linear search and put all nonoverlapping intervals first and then adjust new interval such that overlapping intervals are taken care of, then push remaining intervals to result vector.

65. Valid Number
Main Idea: iterate through string, at every point check for these flags
    boolean pointSeen = false;
    boolean eSeen = false;
    boolean numberSeen = false;
    boolean numberAfterE = true;
keep in mind number can be +ve/-ve


311. Sparse Matrix Multiplication
Main Idea: Create a adjascency list type structure for each sparse matrix. First list stores all cols per row, second list stores rows for each col. Then iterate through all the lists and if entry is same. multiply that and put in resultant matrix.

277. Find the Celebrity
Main Idea: loop through all entries, pick a candidate first, and see if it knows i, if it does, switch the candidate to i otherwise don't. keep doing this while iterating through array. Once done and final candidate is chosen, re-run through array to see if it's indeed the celebrity(satisfy celebrity condition)

187. Repeated DNA Sequences
Main Idea: 2 main points. 1) use a hash-map to store all possible strings of size 10 characters. that means 1st entry will be s[0] - s[9] , 2nd entry could be s[10]-s[19] and when duplicate string seen by hash lookup, count that. 2) Since the size can be huge, reduce per key size because only 4 combinations of letters can be there and for coding each variation minimum bits can be used. like 00 , 01, 10, 11. leetcode solution uses 3 bits, since last 3 bits for A, C, G, T ascii are enough to differentiate between these chars.


149. Max Points on a Line
Main Idea: O(n2) solution using unordered_map<slope, num points with this slope>. Special case, when point is duplicate or verticle. otherwise for every given point, calculate slope and search hashmap to see if slope entry already exists, if it does, increase the number of points by 1 otherwise add a new entry. once all points are inspected, pick the max out of all slope entrtries, duplicates and verticle points. (~roughly)

34. Search for a Range
Main Idea: Do 2 binary searches. 1 for finding start index [condition to check: s[mid-1] != tgt and s[mid] = tgt]. 2nd bin search to find ending index of range.

1. Two Sum
Catch is to return indices and not numbers.
basically create a new vector<pair<int,int>> (number,index in input array). Sort acc to number. and start from 1st last, same algo as finding 2 numbers sum = T

238. Product of Array Except Self
Main Idea: get 2 vectors. 1st stores product vstoe: v0->i-1 and 2nd stores vetos: vn-1->i+1. For any i, output will be vstoe*vetos

101. Symmetric Tree
Main Idea: 
    public boolean isSymmetric(TreeNode root) {
        return root==null || isSymmetricHelp(root.left, root.right);
    }

    private boolean isSymmetricHelp(TreeNode left, TreeNode right){
        if(left==null || right==null)
            return left==right;
        if(left.val!=right.val)
            return false;
        return isSymmetricHelp(left.left, right.right) && isSymmetricHelp(left.right, right.left);
    }

198. House Robber
Main Idea: DP equation : cache[i] = max(nums[i-1] + max_i_2, cache[i-1])

103. Binary Tree Zigzag Level Order Traversal
Main Idea: Do BFS, use queue and stack. queue for bfs and stack for zig-zag direction effect.


464. Can I Win
Main Idea: use hash map to store intermediate results. key being 1 path start to end of choices, value if that path leads to success.
Main idea is to make all possible first choice and then call same function for other player with remaining choices. If for any one of them, the function for 2nd player returns false, then that means since 2nd player lost , first player wins and path is the current key.
here is the code from leetcode.

public class Solution {
    Map<Integer, Boolean> map;
    boolean[] used;
    public boolean canIWin(int maxChoosableInteger, int desiredTotal) {
        int sum = (1+maxChoosableInteger)*maxChoosableInteger/2;
        if(sum < desiredTotal) return false;
        if(desiredTotal <= 0) return true;
        
        map = new HashMap();
        used = new boolean[maxChoosableInteger+1];
        return helper(desiredTotal);
    }
    
    public boolean helper(int desiredTotal){
        if(desiredTotal <= 0) return false;
        int key = format(used);
        if(!map.containsKey(key)){
    // try every unchosen number as next step
            for(int i=1; i<used.length; i++){
                if(!used[i]){
                    used[i] = true;
     // check whether this lead to a win (i.e. the other player lose)
                    if(!helper(desiredTotal-i)){
                        map.put(key, true);
                        used[i] = false;
                        return true;
                    }
                    used[i] = false;
                }
            }
            map.put(key, false);
        }
        return map.get(key);
    }
   
// transfer boolean[] to an Integer 



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

173. Binary Search Tree Iterator
Main Idea: Use stack.
In iterator constructor: while root is valid, push root go to root->left.
hasNext() -> if stk not empty return true;
next() -> get stk top value. if top() has right, temp = top()->right. pop top(). push temp to stack, temp = temp->left until temp valid.


