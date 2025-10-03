#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 4   // 4x4 board for 15-puzzle
#define INF 1000000

// Goal state
int goal[N][N] = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12},
    {13, 14, 15, 0}
};

// Directions for blank movement (up, down, left, right)
int row[] = {1, -1, 0, 0};
int col[] = {0, 0, 1, -1};

// Structure for puzzle state
typedef struct Node {
    int mat[N][N];
    int x, y;          // position of blank tile (0)
    int cost;          // heuristic + level
    int level;         // depth
    struct Node* parent; // pointer to parent node
} Node;

// Utility: Allocate a new node
Node* newNode(int mat[N][N], int x, int y, int newX, int newY, int level, Node* parent) {
    Node* node = (Node*)malloc(sizeof(Node));
    memcpy(node->mat, mat, sizeof(node->mat));
    node->mat[x][y]= node->mat[newX][newY];
    node->mat[newX][newY] = 0;
    node->x = newX;
    node->y = newY;
    node->level = level;
    node->parent = parent;
    node->cost = INF;
    return node;
}

// Count misplaced tiles heuristic
int calculateCost(int mat[N][N]) {
    int count = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (mat[i][j] && mat[i][j] != goal[i][j])
                count++;
    return count;
}

// Print matrix
void printMatrix(int mat[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (mat[i][j] == 0)
                printf("   . ");
            else
                printf("%4d", mat[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Print solution path
void printPath(Node* root) {
    if (root == NULL)
        return;
    printPath(root->parent);
    printMatrix(root->mat);
}

// Min-heap (priority queue) for nodes
typedef struct {
    Node** arr;
    int size;
    int capacity;
} MinHeap;

MinHeap* createHeap(int capacity) {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->arr = (Node**)malloc(capacity * sizeof(Node*));
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void swap(Node** a, Node** b) {
    Node* temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyUp(MinHeap* heap, int idx) {
    while (idx > 0) {
        int parent = (idx - 1) / 2;
        if (heap->arr[parent]->cost > heap->arr[idx]->cost) {
            swap(&heap->arr[parent], &heap->arr[idx]);
            idx = parent;
        } else break;
    }
}

void heapifyDown(MinHeap* heap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < heap->size && heap->arr[left]->cost < heap->arr[smallest]->cost)
        smallest = left;
    if (right < heap->size && heap->arr[right]->cost < heap->arr[smallest]->cost)
        smallest = right;

    if (smallest != idx) {
        swap(&heap->arr[smallest], &heap->arr[idx]);
        heapifyDown(heap, smallest);
    }
}

void pushHeap(MinHeap* heap, Node* node) {
    if (heap->size == heap->capacity) return;
    heap->arr[heap->size] = node;
    heapifyUp(heap, heap->size);
    heap->size++;
}

Node* popHeap(MinHeap* heap) {
    if (heap->size <= 0) return NULL;
    Node* root = heap->arr[0];
    heap->arr[0] = heap->arr[--heap->size];
    heapifyDown(heap, 0);
    return root;
}

// Solve 15 puzzle using Branch and Bound
void solve(int initial[N][N], int x, int y) {
    MinHeap* heap = createHeap(100000);

    Node* root = newNode(initial, x, y, x, y, 0, NULL);
    root->cost = calculateCost(initial);

    pushHeap(heap, root);

    while (heap->size) {
        Node* min = popHeap(heap);

        if (min->cost == 0) {
            printf("\nSolution found at level %d:\n", min->level);
            printPath(min);
            return;
        }

        for (int i = 0; i < 4; i++) {
            int newX = min->x + row[i];
            int newY = min->y + col[i];

            if (newX >= 0 && newX < N && newY >= 0 && newY < N) {
                Node* child = newNode(min->mat, min->x, min->y, newX, newY, min->level + 1, min);
                child->cost = child->level + calculateCost(child->mat);
                pushHeap(heap, child);
            }
        }
    }
}

int main() {
    int initial[N][N];
    int x, y;

    printf("Enter initial 4x4 puzzle state (use 0 for blank):\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &initial[i][j]);
            if (initial[i][j] == 0) {
                x = i;
                y = j;
            }
        }
    }

    solve(initial, x, y);

    return 0;
}
