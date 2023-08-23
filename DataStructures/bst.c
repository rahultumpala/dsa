#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct node
{
    int val;
    struct node *left;
    struct node *right;
};

typedef struct node node;

node *create(int val)
{
    node *n = (node *)malloc(sizeof(node));
    n->val = val;
    n->left = NULL;
    n->right = NULL;
    return n;
}

void printInorder(node *root)
{
    if (root == NULL)
        return;
    if (root->left != NULL)
        printInorder(root->left);
    printf("%d ", root->val);
    if (root->right != NULL)
        printInorder(root->right);
}

void printPostOrder(node *root)
{
    if (root == NULL)
        return;
    if (root->left != NULL)
        printPostOrder(root->left);
    if (root->right != NULL)
        printPostOrder(root->right);
    printf("%d ", root->val);
}

void printPreOrder(node *root)
{
    if (root == NULL)
        return;
    printf("%d ", root->val);
    if (root->left != NULL)
        printPreOrder(root->left);
    if (root->right != NULL)
        printPreOrder(root->right);
}

void insert(node *root, int val)
{
    if (root == NULL)
    {
        root = create(val);
    }
    if (root->val == val)
        return;
    if (root->val > val)
    {
        if (root->left == NULL)
            root->left = create(val);
        else
            insert(root->left, val);
    }
    if (root->val < val)
    {
        if (root->right == NULL)
            root->right = create(val);
        else
            insert(root->right, val);
    }
}

int main(int argc, char **argv)
{
    node *root = create(5);
    insert(root, 1);
    insert(root, 3);
    insert(root, 2);
    insert(root, 4);
    insert(root, 7);
    insert(root, 6);
    insert(root, 8);
    insert(root, 10);
    insert(root, 9);
    printInorder(root);
    printf("\n");
    printPostOrder(root);
    printf("\n");
    printPreOrder(root);
    printf("\n");
    return 0;
}