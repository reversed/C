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
    void reorderList(ListNode* head) {
        if (head == nullptr) return;
        if (head->next == nullptr) return;
        
        ListNode* cur = head->next;
        ListNode* pre = cur;
        while (cur->next != nullptr) {
            pre = cur;
            cur = cur->next;
        }

        ListNode* next_head = head->next;
        head->next = cur;
        cur->next = next_head;
        pre->next = nullptr;
        reorderList(next_head);
    }
};
