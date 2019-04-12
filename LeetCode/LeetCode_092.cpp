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
    ListNode* reverseBetween(ListNode *head, int m, int n) {
        ListNode* res = new ListNode(0);
        res->next = head;
        ListNode* cur = res;
        
        int cnt = m - 1;
        while (cur != NULL && cnt > 0) {
            cur = cur->next;
            --cnt;
        }
        if (cur == NULL) return res->next;
        if (cur->next == NULL) return res->next;
        if (cur->next->next == NULL) return res->next;

        ListNode *st = cur;
        ListNode *ed = cur->next;
        ListNode *p1, *p2, *p3;
        cnt = n - m;
        p1 = cur->next; p2 = p1->next; p3 = p2->next;
        
        while (p2 != NULL && cnt > 0) {
            p2->next = p1;
            p1 = p2; p2 = p3; 
            if (p3 != NULL) p3 = p3->next;
            --cnt;
        }
        st->next = p1;
        ed->next = p2;
        return res->next;
    }
};

