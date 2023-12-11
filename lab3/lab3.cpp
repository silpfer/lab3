#include <iostream>
#include <vector>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(NULL) {}
};

ListNode* task1(ListNode* list1, ListNode* list2) {
    ListNode* dummy = new ListNode(0);
    ListNode* current = dummy;

    while (list1 != NULL && list2 != NULL) {
        if (list1->val <= list2->val) {
            current->next = list1;
            list1 = list1->next;
        }
        else {
            current->next = list2;
            list2 = list2->next;
        }
        current = current->next;
    }

    if (list1 != NULL) {
        current->next = list1;
    }
    else {
        current->next = list2;
    }

    return dummy->next;
}

ListNode* task2(ListNode* head) {
    ListNode* current = head;

    while (current != NULL && current->next != NULL) {
        if (current->val == current->next->val) {
            ListNode* temp = current->next;
            current->next = current->next->next;
            delete temp;
        }
        else {
            current = current->next;
        }
    }

    return head;
}

bool task3(ListNode* head) {
    if (head == NULL || head->next == NULL) {
        return false; 
    }

    ListNode* slow = head; 
    ListNode* fast = head->next; 

    while (slow != fast) {
        if (fast == NULL || fast->next == NULL) {
            return false; 
        }
        slow = slow->next; 
        fast = fast->next->next; 
    }

    return true; 
}

ListNode* newNode(int key)
{
    ListNode* temp = new ListNode(key);
    return temp;
}

void reverselist(ListNode** head)
{
    ListNode* prev = NULL, * curr = *head, * next;

    while (curr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    *head = prev;
}

void task4(ListNode** head) {
    ListNode* slow = *head;
    if (slow == NULL || slow->next == NULL) {
        return;
    }

    ListNode* fast = slow->next;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    ListNode* head1 = *head;
    ListNode* head2 = slow->next;
    slow->next = NULL;

    reverselist(&head2);
    *head = newNode(0); 
    ListNode* curr = *head;
    while (head1 || head2) {
        if (head1) {
            curr->next = head1;
            curr = curr->next;
            head1 = head1->next;
        }
        if (head2) {
            curr->next = head2;
            curr = curr->next;
            head2 = head2->next;
        }
    }
    ListNode* tempHead = *head;
    *head = tempHead->next;
    delete tempHead;
}

void task5(ListNode* node) {
    if (node == NULL || node->next == NULL) {
        return; 
    }

    ListNode* nextNode = node->next; 
    node->val = nextNode->val; 
    node->next = nextNode->next; 
    delete nextNode; 
}

ListNode* task6(ListNode* head)
{
    int n = 0, k = 0;
    while (head)
    {
        n *= 10;
        n += head->val;
        head = head->next;
    }
    n *= 2;
    ListNode* dummy = new ListNode(0);
    ListNode* current = dummy;

    while (n > 0)
    {
        k *= 10;
        k += n % 10;
        n /= 10;       
    }
    while (k > 0)
    {
        int digit = k % 10;
        k /= 10;

        current->next = new ListNode(digit);
        current = current->next;
    }
   
    return dummy->next;
}

ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    if (!l1) return l2;
    if (!l2) return l1;

    if (l1->val < l2->val) {
        l1->next = mergeTwoLists(l1->next, l2);
        return l1;
    }
    else {
        l2->next = mergeTwoLists(l1, l2->next);
        return l2;
    }
}

ListNode* task7(vector<ListNode*>& lists) {
    int k = lists.size();
    if (k == 0) return nullptr;
    if (k == 1) return lists[0];

    while (k > 1) {
        int i = 0, j = k - 1;
        while (i < j) {
            lists[i] = mergeTwoLists(lists[i], lists[j]);
            i++;
            j--;
            if (i >= j) k = j + 1;
        }
    }
    return lists[0];
}

ListNode* task8(ListNode* head, int k) {
    ListNode* current = head;
    int count = 0;

    while (current != NULL && count != k) {
        current = current->next;
        count++;
    }

    if (count == k) {
        current = task8(current, k);
        while (count > 0) {
            ListNode* temp = head->next;
            head->next = current;
            current = head;
            head = temp;
            count--;
        }
        head = current;
    }

    return head;
}

ListNode* task9(ListNode* head, int x) {
    ListNode* less = new ListNode(0);
    ListNode* greaterOrEqual = new ListNode(0);
    ListNode* lessCurrent = less;
    ListNode* greaterOrEqualCurrent = greaterOrEqual;

    while (head != NULL) {
        if (head->val < x) {
            lessCurrent->next = head;
            lessCurrent = lessCurrent->next;
        }
        else {
            greaterOrEqualCurrent->next = head;
            greaterOrEqualCurrent = greaterOrEqualCurrent->next;
        }
        head = head->next;
    }

    lessCurrent->next = greaterOrEqual->next;
    greaterOrEqualCurrent->next = NULL;

    return less->next;
}

void printList(ListNode* head) {
    while (head != NULL) {
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}

int main()
{
    ListNode* list1 = new ListNode(1);
    list1->next = new ListNode(2);
    list1->next->next = new ListNode(4);

    ListNode* list2 = new ListNode(1);
    list2->next = new ListNode(3);
    list2->next->next = new ListNode(4);

    printList(list1);
    printList(list2); 
    //До завдання 1
    ListNode* mergedList = task1(list1, list2); 
    printList(mergedList); 
    //До завдання 2
    ListNode* duplicates = task2(mergedList);
    printList(duplicates);

    ListNode* list3 = new ListNode(3);
    list3->next = new ListNode(2);
    list3->next->next = new ListNode(0);
    list3->next->next->next = new ListNode(-4);
    list3->next->next->next->next = list3->next;
    //До завдання 3
    if (task3(list3))
        cout << "True\n";
    else cout << "False\n";

    if (task3(duplicates))
        cout << "True\n";
    else cout << "False\n";

    ListNode* list4 = new ListNode(1);
    list4->next = new ListNode(2);
    list4->next->next = new ListNode(3);
    list4->next->next->next = new ListNode(4);
    list4->next->next->next->next = new ListNode(5);
    //До завдання 4
    task4(&list4);
    printList(list4);

    printList(duplicates);
    ListNode* nodeToDelete = duplicates->next->next;
    //До завдання 5
    task5(nodeToDelete);
    printList(duplicates);
    //До завдання 6
    ListNode* list5 = task6(list4);
    printList(list4);
    printList(list5);

    ListNode* list6 = new ListNode(1);
    list6->next = new ListNode(4);
    list6->next->next = new ListNode(5);

    ListNode* list7 = new ListNode(1);
    list7->next = new ListNode(3);
    list7->next->next = new ListNode(4);

    ListNode* list8 = new ListNode(2);
    list8->next = new ListNode(6);

    vector<ListNode*> linkedLists = { list6, list7, list8 };
    //До завдання 7
    ListNode* list9 = task7(linkedLists);
    printList(list9);

    ListNode* list10 = new ListNode(1);
    list10->next = new ListNode(2);
    list10->next->next = new ListNode(3);
    list10->next->next->next = new ListNode(4);
    list10->next->next->next->next = new ListNode(5);
    //До завдання 8
    ListNode* list11 = task8(list10, 2);
    printList(list11);

    ListNode* list12 = new ListNode(1);
    list12->next = new ListNode(4);
    list12->next->next = new ListNode(3);
    list12->next->next->next = new ListNode(2);
    list12->next->next->next->next = new ListNode(5);
    list12->next->next->next->next->next = new ListNode(2);
    //До завдання 9
    printList(task9(list12, 3));
    return 0;
}
