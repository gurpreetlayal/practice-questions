/*
Given a binary tree, return the zigzag level order traversal of its nodes' values. (ie, from left to right, then right to left for the next level and alternate between).

For example:
Given binary tree [3,9,20,null,null,15,7],
    3
   / \
  9  20
    /  \
   15   7
return its zigzag level order traversal as:
[
  [3],
  [20,9],
  [15,7]
]

vector<vector<int>> zigzagLevelOrder(TreeNode* root);

*/
#include <stack>
#include <queue>
#include <iostream>
#include <string> 
#include <vector>

using namespace std;

typedef TreeNode node;
vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
    vector<vector<int>> res;
    if (root == nullptr) {
        return vector<vector<int>>(vector<int>());
    }

    Stack<node*> stk;
    Queue<node*> q;

    node* marker = nullptr;

    q.push(root);
    q.push(marker);

    int dir = 0;
    while (!q.empty()) {
        vector<int> pres;

        while (q.front() != marker) {
            if (dir) {
                stk.push(q.front();
            } else {
                pres.push_back(q.front()->val);
            }
            if (q.front()->left) {
                q.push(q.front()->left);
            }
            if (q.front()->right) {
                q.push(q.front()->right);
            }
            q.pop();
        }
        q.pop();
        if (!q.empty()) {
            q.push(marker);
        }
        dir = !dir;
        if (!stk.empty()) {
            pres.push_back(stk.top());
            stk.pop();
        }
        res.push_back(pres);
    }
    return res;
}


int main () {

    return 0;
}
