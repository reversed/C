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
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder,
                        vector<int>::iterator ib, 
                        vector<int>::iterator ie,
                        vector<int>::iterator pc) {
        if (ib >= ie) return nullptr;
        
        //printf("%d %d\n", distance(inorder.begin(), ib), distance(inorder.begin(), ie));
        //printf("%d\n\n", pc - postorder.begin());
        
        TreeNode* res = new TreeNode(*pc);
        vector<int>::iterator it = std::find(ib, ie, *pc);
        
        res->right = buildTree(inorder, postorder, it + 1, ie, pc - 1);
        res->left = buildTree(inorder, postorder, ib, it, pc - (ie - it));
        return res;
    }
    
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        if (inorder.empty() || postorder.empty()) return nullptr;
        return buildTree(inorder, postorder, inorder.begin(), inorder.end(), postorder.end() - 1);
    }
};

