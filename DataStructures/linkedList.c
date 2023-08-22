#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int val;
    struct node *next;
} node;

node *create(int val) {
    node *element = (node *)malloc(sizeof(int));
    element->val = val;
    element->next = NULL;
    return element;
}

void *insertAtHead(node *head, int val) {
    node *newHead = create(val);
    newHead->next = head;
    head = newHead; 
}

void *insertAtEnd(node *head, int val) {
    node *newTail = create(val);
    if(head == NULL) {
        head = newTail;
        return;
    }
    node *h = head;
    while(h->next != NULL) h = h->next;
    h->next = newTail;
}

void insertAtIndex(node *head, int index, int val) {
    node *el = create(val);
    if(head == NULL) {
        head = el;
        return;
    }
    int count = 0;
    node *h = head;
    while (count + 1 < index && h->next != NULL) {
        h = h->next;
        count++;
    }
    if(h->next == NULL && count != index - 1){
        h->next = el;
        return;
    }
    el->next = h->next;
    h->next = el;
}

node *reverse(node *head) {
    if(head == NULL || head->next == NULL) return head;
    node *prev = NULL;
    node *cur = head;
    while(cur != NULL) {
        node *next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }
    return prev;
}

int main(int argc, char **argv) {
    return 0;
}