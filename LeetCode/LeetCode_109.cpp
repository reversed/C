/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
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
    TreeNode* sortedListToBST(ListNode* head) {
        TreeNode* res;
        if (head == nullptr) return nullptr;
        if (head->next == nullptr) {
            res = new TreeNode(head->val);
            return res;
        }
        
        ListNode* slow = head;
        ListNode* fast = head->next;
        
        while (fast != nullptr) {
            if (fast->next == nullptr) break;
            if (fast->next->next == nullptr) break;          
            slow = slow->next;
            fast = fast->next->next;
        }

        ListNode* cur = slow->next;
        ListNode* nxt = cur->next;
        slow->next = nullptr;
        
        res = new TreeNode(cur->val);
        res->left = sortedListToBST(head);
        res->right = sortedListToBST(nxt);
        return res;
    }
};
