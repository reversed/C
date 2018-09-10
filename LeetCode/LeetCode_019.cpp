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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* pre = NULL;
        ListNode* p1 = head;
        ListNode* p2 = head;
        for (int i = 0; i < n; ++i)
        {
            p2 = p2->next;
        }
        
        while (p2 != NULL)
        {
            pre = p1;
            p1 = p1->next;
            p2 = p2->next;
        }
        if (pre != NULL)
        {
            pre->next = p1->next;          
        }
        else
        {
            head = head->next;
        }
        delete p1;
        
        return head;
    }
};

