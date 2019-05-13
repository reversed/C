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
    ListNode *detectCycle(ListNode *head) {
        if (head == nullptr) return nullptr;
        if (head->next == nullptr) return nullptr;
        
        ListNode *tortoise = head;
        ListNode *hare = head->next;
        while (tortoise != hare) {
            if (hare->next == nullptr) return nullptr;
            if (hare->next->next == nullptr) return nullptr;
            tortoise = tortoise->next;
            hare = hare->next->next;
        }
        
        tortoise = head;
        while (hare->next != tortoise) {
            hare = hare->next;
            tortoise = tortoise->next;
        }
        return tortoise;
    }
};

