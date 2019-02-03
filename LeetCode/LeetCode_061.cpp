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
    ListNode* rotateRight(ListNode* head, int k) {
        if (head == NULL) return NULL;
            
        int len = 0;
        ListNode *p0 = head;
        while (p0 != NULL)
        {
            p0 = p0->next;
            ++len;
        }
        k = k % len;
        if (k == 0) return head;
        
        ListNode *p1 = head, *p2 = head;
        for (int i = 0; i < k; ++i) p2 = p2->next;
        
        while (p2->next != NULL)
        {
            p1 = p1->next;
            p2 = p2->next;
        }

        ListNode *tmp = p1->next;
        p1->next = NULL;
        p2->next = head;
        head = tmp;
        return head;    
    }
};

