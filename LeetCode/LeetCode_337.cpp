// Time Limit Exceeded
/*
class Solution {
public:
    int rob(TreeNode* root) {
        if (root == nullptr) return 0;
        
        int max_val = 0;
        int ml = rob(root->left);
        int mll = root->left ? rob(root->left->left) : 0;
        int mlr = root->left ? rob(root->left->right) : 0;

        int mr = rob(root->right);
        int mrl = root->right ? rob(root->right->left) : 0;
        int mrr = root->right ? rob(root->right->right) : 0;
        
        // case 1: with root
        int max1 = root->val + mll + mlr + mrl + mrr;
        
        // case 2: not with root, with root->left
        int tmp = max(mrl + mrr, mr);
        int max2 = ml + tmp;
        
        // case 3: not with root, with root->right
        tmp = max(mll + mlr, ml);
        int max3 = mr + tmp;
        
        return max(max(max1,max2), max3);
    }
};
*/

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
    unordered_map<TreeNode*, int> sums;
    
    int rob(TreeNode* root) {
        if (root == nullptr) return 0;
        if (sums.count(root) != 0) return sums[root];
        
        int max_val = 0;
        int ml = rob(root->left);
        int mll = root->left ? rob(root->left->left) : 0;
        int mlr = root->left ? rob(root->left->right) : 0;

        int mr = rob(root->right);
        int mrl = root->right ? rob(root->right->left) : 0;
        int mrr = root->right ? rob(root->right->right) : 0;
        
        // case 1: with root
        int max1 = root->val + mll + mlr + mrl + mrr;
        
        // case 2: not with root, with root->left
        int tmp = max(mrl + mrr, mr);
        int max2 = ml + tmp;
        
        // case 3: not with root, with root->right
        tmp = max(mll + mlr, ml);
        int max3 = mr + tmp;
        
        sums[root] = max(max(max1,max2), max3);
        
        return sums[root];
    }
};



