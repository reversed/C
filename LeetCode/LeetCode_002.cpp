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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode *res = new ListNode(-1); // head node
        int v = 0, v1 = 0, v2 = 0, c = 0;
        
        ListNode *cur = res;
        while (l1 != NULL && l2 != NULL)
        {
            v1 = l1->val;
            v2 = l2->val;
            v = (v1 + v2 + c) % 10;
            c = (v1 + v2 + c) / 10;    

            cur->next = new ListNode(v);
            cur = cur->next;
            l1 = l1->next;
            l2 = l2->next;
        }       
        while (l1 != NULL)
        {
            v1 = l1->val;
            v = (v1 + c) % 10;
            c = (v1 + c) / 10;
            
            cur->next = new ListNode(v);
            cur = cur->next;
            l1 = l1->next;
        }
        while (l2 != NULL)
        {
            v2 = l2->val;
            v = (v2 + c) % 10;
            c = (v2 + c) / 10;

            cur->next = new ListNode(v);
            cur = cur->next;
            l2 = l2->next;
        }
        
        if (c != 0)
        {
            cur->next = new ListNode(c);
            cur = cur->next;
        }
        
        return res->next;
    }
};

