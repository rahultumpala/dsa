#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_SIZE 4
#define SCALE 2

typedef struct {
    int count;
    int size;
    int *val;
} heap;


void printHeap(heap *h) {
    printf("PRINT: Heap -> Size = %d, Count = %d\n", h->size, h->count);
    int c = 0;
    while(c < h->count){
        printf("%d ", h->val[c++]);
    }
    printf("\n\n");
}

void swap(heap *h, int x, int y){
    int t = h->val[y];
    h->val[y] = h->val[x];
    h->val[x] = t;
}

/*
Heap is a complete binary tree, meaning, all the layers will be filled, except the last layer which may or may not be full.
Nodes in the last layer will be populated from left to right.

Heapify Algorithm:
    Node at position x will be compared with its children, at positions (2*x+1, 2*x+2)
        Min Heap:
        if either child's val is lesser than parent val, swap them
        Max heap:
        If either child's val is greater than parent val, swap them
    If a swap occurs then heapify the swapped child node agian.
*/
void heapify(heap *h, int parent) {
    // parent's parentIndex will be (parent-1)/2
    int child1 = 2*parent + 1, child2 = 2*parent + 2;
    int min = parent;    

    // Min heap
    if( child1 < h->count && h->val[parent] > h->val[child1] ) min = child1;
    if( child2 < h->count && h->val[min] > h->val[child2] ) min = child2;

    if(min != parent) {
        // modifications occurred
        swap(h, min, parent);
        heapify(h, min);
    }
}

int pop(heap *h) {
    if(h->count == 0) {
        fprintf(stderr, "Cannot pop from empty queue.");
        return -1;
    }
    int min = h->val[0];
    h->val[0] = h->val[h->count - 1];
    h->count--;
    heapify(h, 0);
    return min;
}

void push(heap *h, int val) {
    if(h->count == h->size) {
        h->size = h->size * SCALE;
        h->val = (int *)realloc(h->val, sizeof(int) * h->size);
    }
    h->val[h->count] = val;

    /*
        bubbling up the value as long as the index and its parent
        do not satisfy min heap property: heap[parent] < heap[index]
    */
    
    int index = h->count++;
    int parent = (index -1) / 2;
    while(index > 0 && h->val[parent] > h->val[index]) {
        swap(h, parent, index);
        index = parent;
        parent = (index-1) / 2;
    }
}

heap *intHeap(int size) {
    heap *h = (heap *)malloc(sizeof(h));
    h->val = (int*)malloc(sizeof(int) * size);
    h->size = size;
    h->count = 0;
    return h;
}

int main(int argc, char **argv) {
    heap *h = intHeap(DEFAULT_SIZE);
    push(h, 8);
    push(h, 7);
    push(h, 6);
    push(h, 5);
    push(h, 4);
    push(h, 3);
    push(h, 2);
    push(h, 1);
    printf("POP: top = %d\n", pop(h));
    printHeap(h);
    printf("POP: top = %d\n", pop(h));
    printHeap(h);
    printf("POP: top = %d\n", pop(h));
    printHeap(h);
    printf("POP: top = %d\n", pop(h));
    printHeap(h);
    printf("POP: top = %d\n", pop(h));
    printHeap(h);
    push(h, -1);
    push(h, -2);
    printf("POP: top = %d\n", pop(h));
    printHeap(h);

    return 0;
}