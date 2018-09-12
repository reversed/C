/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        if (head == NULL || head->next == NULL) return head;
        
        ListNode* n1 = head;
        ListNode* n2 = head->next;
        ListNode* n3 = swapPairs(n2->next);
        
        n2->next = n1;
        n1->next = n3;
        return n2;
    }
};







