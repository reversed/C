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
    TreeNode* newTree(TreeNode* head, int v)
    {
        if (head == NULL) return NULL;
        TreeNode *node = new TreeNode(head->val + v);
        node->left = newTree(head->left, v);
        node->right = newTree(head->right, v);
        return node;
    }
    
    vector<TreeNode*> generateTrees(int n) {
        if (n == 0) return {};

        vector<vector<TreeNode*>> dp(n+1);      
        dp[0] = { NULL };
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 0; j < i; ++j)
            {            
                for (auto ln : dp[j])
                {
                    for (auto rn : dp[i - 1 - j])
                    {
                        TreeNode* node = new TreeNode(j+1);
                        node->left = newTree(ln, 0);
                        node->right = newTree(rn, j+1);
                        dp[i].push_back(node);
                    }
                }
            }
        }
        return dp[n];
    }
};
