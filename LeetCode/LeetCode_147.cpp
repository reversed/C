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
    ListNode* ithNode(ListNode* head, int idx) {
        for (int i = 0; i < idx; ++i) head = head->next;
        return head;
    }
    
    ListNode* insertionSortList(ListNode* head) {
        ListNode* new_head = new ListNode(INT_MIN);
        new_head->next = head;
        
        int len = 0;
        ListNode* cur = new_head;
        while (cur != nullptr) {
            cur = cur->next;
            ++len;
        }
        
        for (int i = 1; i < len; ++i) {
            ListNode* l1 = new_head;
            ListNode* l2 = ithNode(new_head, i);
            for (int j = 0; j < i; ++j) {
                if (l1->val <= l2->val) {
                    l1 = l1->next;
                }
                else {
                    ListNode* tmp = ithNode(new_head, i-1);
                    tmp->next = l2->next;

                    tmp = ithNode(new_head, j-1);
                    tmp->next = l2;
                    l2->next = l1;
                    break;
                }
            }
        }
        return new_head->next;
    }
};
