#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define T 3   // Minimum degree

struct BTreeNode {
    int keys[2*T - 1];           
    struct BTreeNode *children[2*T]; 
    int n;                        
    bool leaf;                    
};

// -------- Node Creation --------
struct BTreeNode* createNode(bool leaf) {
    struct BTreeNode* node = (struct BTreeNode*)malloc(sizeof(struct BTreeNode));
    node->leaf = leaf;
    node->n = 0;
    for (int i = 0; i < 2*T; i++)
        node->children[i] = NULL;
    return node;
}

struct BTreeNode* createTree() {
    return createNode(true); 
}

// -------- Search --------
struct BTreeNode* searchItem(struct BTreeNode* root, int key) {
    if (root == NULL) return NULL;
    int i = 0;
    while (i < root->n && key > root->keys[i])
        i++;
    if (i < root->n && root->keys[i] == key)
        return root;
    if (root->leaf) return NULL;
    return searchItem(root->children[i], key);
}

// -------- Split Child --------
void splitChild(struct BTreeNode* x, int i, struct BTreeNode* y) {
    struct BTreeNode* z = createNode(y->leaf);
    z->n = T - 1;

    for (int j = 0; j < T-1; j++)
        z->keys[j] = y->keys[j+T];

    if (!y->leaf) {
        for (int j = 0; j < T; j++)
            z->children[j] = y->children[j+T];
    }

    y->n = T - 1;

    for (int j = x->n; j >= i+1; j--)
        x->children[j+1] = x->children[j];
    x->children[i+1] = z;

    for (int j = x->n-1; j >= i; j--)
        x->keys[j+1] = x->keys[j];
    x->keys[i] = y->keys[T-1];
    x->n++;
}

// -------- Insert --------
void insertNonFull(struct BTreeNode* x, int k) {
    int i = x->n - 1;
    if (x->leaf) {
        while (i >= 0 && k < x->keys[i]) {
            x->keys[i+1] = x->keys[i];
            i--;
        }
        x->keys[i+1] = k;
        x->n++;
    } else {
        while (i >= 0 && k < x->keys[i])
            i--;
        if (x->children[i+1]->n == 2*T-1) {
            splitChild(x, i+1, x->children[i+1]);
            if (k > x->keys[i+1])
                i++;
        }
        insertNonFull(x->children[i+1], k);
    }
}

struct BTreeNode* insertItem(struct BTreeNode* root, int k) {
    if (root->n == 2*T-1) {
        struct BTreeNode* s = createNode(false);
        s->children[0] = root;
        splitChild(s, 0, root);
        int i = 0;
        if (s->keys[0] < k)
            i++;
        insertNonFull(s->children[i], k);
        return s; 
    } else {
        insertNonFull(root, k);
        return root;
    }
}

// -------- Traverse --------
void traverse(struct BTreeNode* root) {
    if (root == NULL) return;
    int i;
    for (i = 0; i < root->n; i++) {
        if (!root->leaf)
            traverse(root->children[i]);
        printf("%d ", root->keys[i]);
    }
    if (!root->leaf)
        traverse(root->children[i]);
}

// -------- Deletion Helpers --------
int getPredecessor(struct BTreeNode* node) {
    struct BTreeNode* cur = node;
    while (!cur->leaf)
        cur = cur->children[cur->n];
    return cur->keys[cur->n - 1];
}

int getSuccessor(struct BTreeNode* node) {
    struct BTreeNode* cur = node;
    while (!cur->leaf)
        cur = cur->children[0];
    return cur->keys[0];
}

void merge(struct BTreeNode* x, int idx) {
    struct BTreeNode* child = x->children[idx];
    struct BTreeNode* sibling = x->children[idx+1];

    child->keys[T-1] = x->keys[idx];
    for (int i = 0; i < sibling->n; ++i)
        child->keys[i+T] = sibling->keys[i];
    if (!child->leaf) {
        for (int i = 0; i <= sibling->n; ++i)
            child->children[i+T] = sibling->children[i];
    }
    for (int i = idx+1; i < x->n; ++i)
        x->keys[i-1] = x->keys[i];
    for (int i = idx+2; i <= x->n; ++i)
        x->children[i-1] = x->children[i];
    child->n += sibling->n + 1;
    x->n--;
    free(sibling);
}

void borrowFromPrev(struct BTreeNode* x, int idx) {
    struct BTreeNode* child = x->children[idx];
    struct BTreeNode* sibling = x->children[idx-1];
    for (int i = child->n-1; i >= 0; --i)
        child->keys[i+1] = child->keys[i];
    if (!child->leaf) {
        for (int i = child->n; i >= 0; --i)
            child->children[i+1] = child->children[i];
    }
    child->keys[0] = x->keys[idx-1];
    if (!child->leaf)
        child->children[0] = sibling->children[sibling->n];
    x->keys[idx-1] = sibling->keys[sibling->n-1];
    child->n += 1;
    sibling->n -= 1;
}

void borrowFromNext(struct BTreeNode* x, int idx) {
    struct BTreeNode* child = x->children[idx];
    struct BTreeNode* sibling = x->children[idx+1];
    child->keys[child->n] = x->keys[idx];
    if (!child->leaf)
        child->children[child->n+1] = sibling->children[0];
    x->keys[idx] = sibling->keys[0];
    for (int i = 1; i < sibling->n; ++i)
        sibling->keys[i-1] = sibling->keys[i];
    if (!sibling->leaf) {
        for (int i = 1; i <= sibling->n; ++i)
            sibling->children[i-1] = sibling->children[i];
    }
    child->n += 1;
    sibling->n -= 1;
}

void fill(struct BTreeNode* x, int idx) {
    if (idx != 0 && x->children[idx-1]->n >= T)
        borrowFromPrev(x, idx);
    else if (idx != x->n && x->children[idx+1]->n >= T)
        borrowFromNext(x, idx);
    else {
        if (idx != x->n)
            merge(x, idx);
        else
            merge(x, idx-1);
    }
}

void deleteFromNode(struct BTreeNode* x, int k) {
    int idx = 0;
    while (idx < x->n && x->keys[idx] < k)
        ++idx;

    if (idx < x->n && x->keys[idx] == k) {
        if (x->leaf) {
            for (int i = idx+1; i < x->n; ++i)
                x->keys[i-1] = x->keys[i];
            x->n--;
        } else {
            if (x->children[idx]->n >= T) {
                int pred = getPredecessor(x->children[idx]);
                x->keys[idx] = pred;
                deleteFromNode(x->children[idx], pred);
            } else if (x->children[idx+1]->n >= T) {
                int succ = getSuccessor(x->children[idx+1]);
                x->keys[idx] = succ;
                deleteFromNode(x->children[idx+1], succ);
            } else {
                merge(x, idx);
                deleteFromNode(x->children[idx], k);
            }
        }
    } else {
        if (x->leaf) {
            printf("Key %d not found in B-Tree\n", k);
            return;
        }
        bool flag = (idx == x->n);
        if (x->children[idx]->n < T)
            fill(x, idx);
        if (flag && idx > x->n)
            deleteFromNode(x->children[idx-1], k);
        else
            deleteFromNode(x->children[idx], k);
    }
}

struct BTreeNode* deleteItem(struct BTreeNode* root, int k) {
    if (!root) return root;
    deleteFromNode(root, k);
    if (root->n == 0) {
        struct BTreeNode* tmp = root;
        if (root->leaf)
            root = NULL;
        else
            root = root->children[0];
        free(tmp);
    }
    return root;
}

// -------- Cleanup --------
void deleteTree(struct BTreeNode* root) {
    if (root == NULL) return;
    if (!root->leaf) {
        for (int i = 0; i <= root->n; i++)
            deleteTree(root->children[i]);
    }
    free(root);
}

// -------- Main --------
int main() {
    struct BTreeNode* root = createTree();
    int keys[] = {10, 20, 5, 6, 12, 30, 7, 17};
    int n = sizeof(keys)/sizeof(keys[0]);
    for (int i = 0; i < n; i++)
        root = insertItem(root, keys[i]);

    printf("B-Tree traversal: ");
    traverse(root);
    printf("\n");

    int searchKey = 6;
    if (searchItem(root, searchKey))
        printf("Key %d found in B-Tree\n", searchKey);
    else
        printf("Key %d not found in B-Tree\n", searchKey);

    // Deletion tests
    printf("\nDeleting key 6...\n");
    root = deleteItem(root, 6);
    traverse(root); printf("\n");

    printf("Deleting key 13...\n");
    root = deleteItem(root, 13);
    traverse(root); printf("\n");

    printf("Deleting key 7...\n");
    root = deleteItem(root, 7);
    traverse(root); printf("\n");

    printf("Deleting key 4...\n");
    root = deleteItem(root, 4);
    traverse(root); printf("\n");

    printf("Deleting key 2...\n");
    root = deleteItem(root, 2);
    traverse(root); printf("\n");

    printf("Deleting key 16...\n");
    root = deleteItem(root, 16);
    traverse(root); printf("\n");

    deleteTree(root);
    return 0;
}
