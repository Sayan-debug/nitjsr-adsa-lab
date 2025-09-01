#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int front, rear, size;
    unsigned capacity;
    int* array;
} Queue;

Queue* createQueue(unsigned capacity) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->rear = capacity - 1; 
    queue->array = (int*)malloc(queue->capacity * sizeof(int));
    return queue;
}

int isFull(Queue* queue) { return (queue->size == queue->capacity); }
int isEmpty(Queue* queue) { return (queue->size == 0); }

void enqueue(Queue* queue, int item) {
    if (isFull(queue)) return;
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size++;
}

int dequeue(Queue* queue) {
    if (isEmpty(queue)) return -1;
    int item = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
    return item;
}

int front(Queue* queue) {
    if (isEmpty(queue)) return -1;
    return queue->array[queue->front];
}

typedef struct {
    Queue *q1, *q2;
} StackEnqCostly;

StackEnqCostly* createStackEnqCostly(int capacity) {
    StackEnqCostly* s = (StackEnqCostly*)malloc(sizeof(StackEnqCostly));
    s->q1 = createQueue(capacity);
    s->q2 = createQueue(capacity);
    return s;
}

void pushEnqCostly(StackEnqCostly* s, int x) {
    enqueue(s->q2, x);

    while (!isEmpty(s->q1)) {
        enqueue(s->q2, dequeue(s->q1));
    }

    Queue* temp = s->q1;
    s->q1 = s->q2;
    s->q2 = temp;
}

int popEnqCostly(StackEnqCostly* s) {
    if (isEmpty(s->q1)) {
        printf("Stack is empty\n");
        return -1;
    }
    return dequeue(s->q1);
}

typedef struct {
    Queue *q1, *q2;
} StackDeqCostly;

StackDeqCostly* createStackDeqCostly(int capacity) {
    StackDeqCostly* s = (StackDeqCostly*)malloc(sizeof(StackDeqCostly));
    s->q1 = createQueue(capacity);
    s->q2 = createQueue(capacity);
    return s;
}

void pushDeqCostly(StackDeqCostly* s, int x) {
    enqueue(s->q1, x);
}

int popDeqCostly(StackDeqCostly* s) {
    if (isEmpty(s->q1)) {
        printf("Stack is empty\n");
        return -1;
    }

    while (s->q1->size > 1) {
        enqueue(s->q2, dequeue(s->q1));
    }

    int popped = dequeue(s->q1);

    Queue* temp = s->q1;
    s->q1 = s->q2;
    s->q2 = temp;

    return popped;
}

int main() {
    printf("=== Method 1: EnQueue costly ===\n");
    StackEnqCostly* s1 = createStackEnqCostly(10);
    pushEnqCostly(s1, 10);
    pushEnqCostly(s1, 20);
    pushEnqCostly(s1, 30);
    printf("Popped: %d\n", popEnqCostly(s1));
    printf("Popped: %d\n", popEnqCostly(s1));

    printf("\n=== Method 2: DeQueue costly ===\n");
    StackDeqCostly* s2 = createStackDeqCostly(10);
    pushDeqCostly(s2, 10);
    pushDeqCostly(s2, 20);
    pushDeqCostly(s2, 30);
    printf("Popped: %d\n", popDeqCostly(s2));
    printf("Popped: %d\n", popDeqCostly(s2));

    return 0;
}
