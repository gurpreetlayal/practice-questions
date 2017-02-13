#include "l.h"

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

bool isThere (TreeNode* root, TreeNode* node) {
    if (root == nullptr || node == nullptr) {  return false; }
    if (root->val == node->val) { return true; }
    
    return (isThere(root->left, node) || isThere(root->right, node));
}

TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (root == nullptr || p == nullptr || q == nullptr) {
        return nullptr;
    }

    if ((root == p && root == q) ||
        (root == p) && (((root->left && isThere(root->left, q)) || (root->right && isThere(root->right, q)))) ||
        (root == q) && (((root->left && isThere(root->left, p)) || (root->right && isThere(root->right, p)))) ||
        (isThere(root->left, p) && isThere(root->right, q)) ||
        (isThere(root->right, p) && isThere(root->left, q))) {
        return root;
    } else {
        return nullptr;
    }
}

int main() {

    return 0;
}
