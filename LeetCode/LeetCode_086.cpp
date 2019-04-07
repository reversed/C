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
    ListNode* partition(ListNode* head, int x) {
        ListNode *p1 = new ListNode(0);
        ListNode *p2 = new ListNode(0);
        ListNode *new_head1 = p1;
        ListNode *new_head2 = p2;
        
        while (head != nullptr)
        {
            if (head->val < x)
            {
                p1->next = new ListNode(head->val);
                p1 = p1->next;
            }
            else
            {
                p2->next = new ListNode(head->val);
                p2 = p2->next;
            }
            head = head->next;
        }
        p1->next = new_head2->next;
        
        return new_head1->next;
    }
};

