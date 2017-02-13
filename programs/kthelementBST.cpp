
int totalElem (TreeNode* root) {
    if (root == NULL) return 0;

    return 1 + totalElem(root->left) + totalElem(root->right);
}

int kthElement (TreeNode* root, int k) {
    if (root == NULL) return INT_MIN;

    auto numElemLeft = totalElem(root->left);

    if (numElemLeft + 1 == k) {
        return root->val;
    }

    if (numElemLeft >= k) {
        return kthElement(root->left, k);
    } else {
        return kthElement(root->right, k - numElemLeft - 1);
    }
}
