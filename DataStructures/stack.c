#include <stdio.h>
#include <stdlib.h>

#define STACK_SIZE 8
#define SCALE 2
#define GROW_CAPACITY(val) (val)*SCALE

#define DEBUG

typedef struct {
    int size;
    int count;
    int *val;
} stack;

void printStack(stack *stk) {
    int cnt = stk->count;
    while(cnt > 0){
        printf(" %d ", stk->val[--cnt]);
    }
    printf("\n");
}

int pop(stack *stk){
    if(stk->count == 0 || stk->size == 0){
        fprintf(stderr, "Cannot pop from empty stack.\n");
        exit(1);
    }
    #ifdef DEBUG
        printf("POP\n");
        stk->count--;
        printStack(stk);
        return stk->val[stk->count+1];
    #endif
    return stk->val[stk->count--];
}

void push(stack *stk, int val) {
    if(stk->count == stk->size) {
        stk->size = GROW_CAPACITY(stk->size);
        void *newVal = realloc( (void *)stk->val, stk->size * sizeof(int) );
        if(newVal == NULL) {
            fprintf(stderr, "Not enough memory.\n");
            exit(2);
        }
        stk->val = newVal;
    }
    stk->val[stk->count++] = val;
    #ifdef DEBUG
        printf("PUSH %d\n",val);
        printStack(stk);
    #endif
}

stack *intStack(int size) {
    // INT Stack
    stack *stk = (stack *) malloc(sizeof(stack));
    stk->val = (int *) malloc(size * sizeof(int));
    stk->size = size;
    stk->count = 0;
    return stk;
}

int main(int argc, char **argv) {
    stack *stk = intStack(STACK_SIZE);
    push(stk, 1);
    push(stk, 2);
    push(stk, 3);
    push(stk, 4);
    push(stk, 5);
    push(stk, 6);
    push(stk, 7);
    push(stk, 8);
    push(stk, 9);
    push(stk, 10);
    push(stk, 11);
    pop(stk);
    pop(stk);
    pop(stk);
    pop(stk);
    pop(stk);
    pop(stk);
    pop(stk);
    pop(stk);
    push(stk, 101);
    push(stk, 102);
    push(stk, 103);
    push(stk, 104);
    push(stk, 105);
}