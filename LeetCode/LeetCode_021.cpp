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
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if (l1 == NULL && l2 == NULL) return NULL;
        if (l1 == NULL) return l2;
        if (l2 == NULL) return l1;
        
        ListNode* res = (struct ListNode*)malloc(sizeof(struct ListNode));
        ListNode* cur = res;

        while (l1 != NULL || l2 != NULL)
        {
            int v1 = 0, v2 = 0;
            if (l1 == NULL) v1 = INT_MAX;
            if (l2 == NULL) v2 = INT_MAX;
            if (l1 != NULL) v1 = l1->val;
            if (l2 != NULL) v2 = l2->val;
            
            ListNode* ln = (struct ListNode*)malloc(sizeof(struct ListNode));
            ln->next = NULL;

            if (v1 > v2)
            {
                ln->val = v2;

                l2 = l2->next;
            }
            else
            {
                ln->val = v1;
                l1 = l1->next;
            }
            cur->next = ln;
            cur = cur->next;
        }
                                                    
        return res->next;
    }
};

