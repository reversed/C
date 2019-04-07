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
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode* new_head = new ListNode(0);
        new_head->next = head;
        
        ListNode *p1 = new_head, *p2 = head;
        
        bool dup = false;
        int dup_val = 0;
        while (p2 != NULL)
        {
            if (p2->next != NULL)
            {
                if (p2->val == p2->next->val)
                {
                    dup = true;
                    dup_val = p2->val;
                }
            }
            
            if (!dup)
            {
                p1 = p2;
                p2 = p2->next;
                continue;
            }
            
            // delete dups
            while (p2 != NULL && p2->val == dup_val)
            {
                ListNode *tmp = p2->next;
                delete p2;
                p2 = tmp;
            }
            p1->next = p2;
            dup = false; 
        }
        return new_head->next;
    }
};

