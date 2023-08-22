#include <stdio.h>
#include <stdlib.h>

#define Q_SIZE 8
#define SCALE 2

struct item {
    int val;
    struct item *next;
    struct item *prev;
};

typedef struct item item;

typedef struct {
    int count;
    item *start;
    item *end;
} queue;


/*
fill from Right to left 
        queue
enq 1 = 1
enq 2 = 2 1
enq 3 = 3 2 1
dq    = 3 2  // return 1
dq    = 3    // return 2
dq    =      // return 3
*/

void printQ(queue *q) {
    if(q->count == 0) return;
    item *ptr = q->start;
    while(ptr != NULL) {
        printf("%d ", ptr->val);
        ptr = ptr->next;
    }
    printf("\n");
}

item *create(int val) {
    item *itm = (item *)malloc(sizeof(item));
    itm->val = val;
    itm->next = NULL;
    itm->prev = NULL;
}

int deque(queue *q) {
    if (q->count == 0) {
        fprintf(stderr, "Cannot deque from empty queue.\n");
        exit(1);
    }
    if(q->count == 1) {
        int ans = q->end->val;
        free(q->end);
        free(q->start);
        return ans;
    }
    int ans = q->end->val;
    item *last = q->end;
    q->end = q->end->prev;
    q->end->next = NULL;
    free(last);
}

void enqueue(queue *q, int val) {
    item *itm = create(val);
    if(q->count == 0){
        q->start = itm;
        q->end = itm;
        q->count++;
        return;
    }
    itm->next = q->start;
    q->start->prev = itm;
    q->start = itm;
    q->count++;
}

queue *intQ() {
    queue *q = (queue *)malloc(sizeof(queue));
    q->count = 0;
    q->start = NULL;
    q->end = NULL;
}

int main(int argc, char **argv) {
    queue *q  = intQ();
    enqueue(q, 1);
    enqueue(q, 2);
    enqueue(q, 3);
    enqueue(q, 4);
    enqueue(q, 5);
    enqueue(q, 6);
    enqueue(q, 7);
    enqueue(q, 8);
    enqueue(q, 9);
    enqueue(q, 10);
    printQ(q);
    deque(q);
    deque(q);
    deque(q);
    deque(q);
    deque(q);
    deque(q);
    enqueue(q, 1);
    enqueue(q, 2);
    enqueue(q, 3);
    enqueue(q, 4);
    enqueue(q, 5);
    enqueue(q, 6);
    printQ(q);
}