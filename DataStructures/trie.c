#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


struct node {
    char val;
    bool isEnd;
    struct node** children;
};
typedef struct node node;

node *create(char c){
    node *n = (node *)malloc(sizeof(node));
    n->val = c;
    n->isEnd = false;
    n->children = (node**) malloc( 26 * sizeof(node));
    return n;
}

node *trie() {
    node *root = create('c');
    return root;
}

void insert(node *root, int len, char *string) {
    int idx = 0;
    node *cur = root;
    while(idx < len) {
        int val = string[idx] - 'a';
        if(cur->children[val] == NULL){
            cur->children[val] = create(string[idx]);
        }
        cur = cur->children[val];
        idx++;
    }
    cur->isEnd = 1;
}

bool search(node *root, int len, char *string) {
    if(len == 0) return NULL;

    char c = string[0];
    if(root->children[c-'a'] == NULL) return NULL;

    int idx = 0;
    node *cur = root;
    while(idx < len) {
        int offset = string[idx] - 'a';
        if(cur->children[offset] == NULL) break;
        idx++;
        cur = cur->children[offset];
    }
    return idx == len && cur->isEnd;
}

int main(int argc, char **argv) {
    node *root = trie();
    insert(root, 5, "hello");
    insert(root, 5, "world");
    insert(root, 2, "hi");
    insert(root, 5, "there");
    insert(root, 6, "offset");
    insert(root, 10, "half-baked");
    insert(root, 4, "half");
    printf("SEARCH %10s - PRESENT? - %5s\n", "half", search(root, 4, "half") == 1 ? "true": "false");
    printf("SEARCH %10s - PRESENT? - %5s\n", "half-moon", search(root, 9, "half-moon") == 1 ? "true": "false");
    printf("SEARCH %10s - PRESENT? - %5s\n", "hello", search(root, 5, "hello") == 1 ? "true": "false");
    printf("SEARCH %10s - PRESENT? - %5s\n", "offset", search(root, 6, "offset") == 1 ? "true": "false");
    printf("SEARCH %10s - PRESENT? - %5s\n", "therapy", search(root, 7, "therapy") == 1 ? "true": "false");
    printf("SEARCH %10s - PRESENT? - %5s\n", "hi", search(root, 2, "hi") == 1 ? "true": "false");
    printf("SEARCH %10s - PRESENT? - %5s\n", "him", search(root, 3, "him") == 1 ? "true": "false");
    return 0;
}