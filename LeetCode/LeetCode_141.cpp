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
    bool hasCycle(ListNode *head) {
        if (head == nullptr) return false;
        if (head->next == nullptr) return false;
        ListNode *tortoise = head;
        ListNode *hare = head->next;
        
        while (hare != tortoise) {
            if (hare->next == nullptr) return false;
            if (hare->next->next == nullptr) return false;
            
            tortoise = tortoise->next;
            hare = hare->next->next;
        }
        return true;
    }
};

