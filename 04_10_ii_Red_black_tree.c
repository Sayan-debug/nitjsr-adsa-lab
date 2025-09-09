#include <stdio.h>
#include <stdlib.h>

typedef enum { RED, BLACK } Color;

typedef struct RBNode {
    int data;
    Color color;
    struct RBNode *left, *right, *parent;
} RBNode;

typedef struct RBTree {
    RBNode *root;
    RBNode *nil; 
} RBTree;

RBTree* createTree() {
    RBTree* tree = (RBTree*)malloc(sizeof(RBTree));
    tree->nil = (RBNode*)malloc(sizeof(RBNode));
    tree->nil->color = BLACK;
    tree->nil->left = tree->nil->right = tree->nil->parent = NULL;
    tree->root = tree->nil;
    return tree;
}
RBNode* newNode(RBTree *tree, int data) {
    RBNode* node = (RBNode*)malloc(sizeof(RBNode));
    node->data = data;
    node->color = RED;
    node->left = node->right = node->parent = tree->nil;
    return node;
}
void leftRotate(RBTree *tree, RBNode *x) {
    RBNode *y = x->right;
    x->right = y->left;
    if (y->left != tree->nil)
        y->left->parent = x;

    y->parent = x->parent;
    if (x->parent == tree->nil)
        tree->root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}
void rightRotate(RBTree *tree, RBNode *y) {
    RBNode *x = y->left;
    y->left = x->right;
    if (x->right != tree->nil)
        x->right->parent = y;

    x->parent = y->parent;
    if (y->parent == tree->nil)
        tree->root = x;
    else if (y == y->parent->right)
        y->parent->right = x;
    else
        y->parent->left = x;

    x->right = y;
    y->parent = x;
}
void insertFixup(RBTree *tree, RBNode *z) {
    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            RBNode *y = z->parent->parent->right;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(tree, z);
                }
                z->parent->color = BLACK;  
                z->parent->parent->color = RED;
                rightRotate(tree, z->parent->parent);
            }
        } else {
            RBNode *y = z->parent->parent->left;
            if (y->color == RED) { 
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) { 
                    z = z->parent;
                    rightRotate(tree, z);
                }
                z->parent->color = BLACK; 
                z->parent->parent->color = RED;
                leftRotate(tree, z->parent->parent);
            }
        }
    }
    tree->root->color = BLACK;
}
void insertItem(RBTree *tree, int data) {
    RBNode *z = newNode(tree, data);
    RBNode *y = tree->nil;
    RBNode *x = tree->root;

    while (x != tree->nil) {
        y = x;
        if (z->data < x->data)
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;
    if (y == tree->nil)
        tree->root = z;
    else if (z->data < y->data)
        y->left = z;
    else
        y->right = z;

    insertFixup(tree, z);
}
void transplant(RBTree *tree, RBNode *u, RBNode *v) {
    if (u->parent == tree->nil)
        tree->root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    v->parent = u->parent;
}
RBNode* treeMinimum(RBTree *tree, RBNode *x) {
    while (x->left != tree->nil)
        x = x->left;
    return x;
}
void deleteFixup(RBTree *tree, RBNode *x) {
    while (x != tree->root && x->color == BLACK) {
        if (x == x->parent->left) {
            RBNode *w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(tree, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(tree, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                leftRotate(tree, x->parent);
                x = tree->root;
            }
        } else {
            RBNode *w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rightRotate(tree, x->parent);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(tree, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rightRotate(tree, x->parent);
                x = tree->root;
            }
        }
    }
    x->color = BLACK;
}
void deleteItem(RBTree *tree, RBNode *z) {
    RBNode *y = z;
    RBNode *x;
    Color yOriginalColor = y->color;

    if (z->left == tree->nil) {
        x = z->right;
        transplant(tree, z, z->right);
    } else if (z->right == tree->nil) {
        x = z->left;
        transplant(tree, z, z->left);
    } else {
        y = treeMinimum(tree, z->right);
        yOriginalColor = y->color;
        x = y->right;
        if (y->parent == z)
            x->parent = y;
        else {
            transplant(tree, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(tree, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    free(z);

    if (yOriginalColor == BLACK)
        deleteFixup(tree, x);
}

RBNode* searchItem(RBTree *tree, int key) {
    RBNode *current = tree->root;
    while (current != tree->nil && key != current->data) {
        if (key < current->data)
            current = current->left;
        else
            current = current->right;
    }
    return current;
}

void freeSubTree(RBTree *tree, RBNode *node) {
    if (node != tree->nil) {
        freeSubTree(tree, node->left);
        freeSubTree(tree, node->right);
        free(node);
    }
}

void deleteTree(RBTree *tree) {
    freeSubTree(tree, tree->root);
    free(tree->nil);
    free(tree);
}



void inorder(RBTree *tree, RBNode *node) {
    if (node != tree->nil) {
        inorder(tree, node->left);
        printf("%d(%s) ", node->data, node->color == RED ? "R" : "B");
        inorder(tree, node->right);
    }
}
int main() {
    RBTree *tree = createTree();

    insertItem(tree, 10);
    insertItem(tree, 20);
    insertItem(tree, 30);
    insertItem(tree, 15);
    insertItem(tree, 25);

    printf("Inorder traversal: ");
    inorder(tree, tree->root);
    printf("\n");

    RBNode *found = searchItem(tree, 15);
    if (found != tree->nil)
        printf("Found: %d\n", found->data);
    else
        printf("Not found\n");

    deleteItem(tree, found);

    printf("After deletion: ");
    inorder(tree, tree->root);
    printf("\n");

    deleteTree(tree);
    return 0;
}
