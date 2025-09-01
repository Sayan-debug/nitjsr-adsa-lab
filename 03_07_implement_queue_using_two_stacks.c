#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int top;
    int capacity;
    int *array;
} Stack;

Stack* createStack(int capacity) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int*)malloc(stack->capacity * sizeof(int));
    return stack;
}

int isFull(Stack* stack) {
    return stack->top == stack->capacity - 1;
}

int isEmpty(Stack* stack) {
    return stack->top == -1;
}

void push(Stack* stack, int item) {
    if (isFull(stack)) return;
    stack->array[++stack->top] = item;
}

int pop(Stack* stack) {
    if (isEmpty(stack)) return -1;
    return stack->array[stack->top--];
}

int peek(Stack* stack) {
    if (isEmpty(stack)) return -1;
    return stack->array[stack->top];
}

typedef struct {
    Stack *stack1, *stack2;
} QueuePushCostly;

QueuePushCostly* createQueuePushCostly(int capacity) {
    QueuePushCostly* q = (QueuePushCostly*)malloc(sizeof(QueuePushCostly));
    q->stack1 = createStack(capacity);
    q->stack2 = createStack(capacity);
    return q;
}

void enqueuePushCostly(QueuePushCostly* q, int item) {
    while (!isEmpty(q->stack1)) {
        push(q->stack2, pop(q->stack1));
    }

    push(q->stack1, item);

    while (!isEmpty(q->stack2)) {
        push(q->stack1, pop(q->stack2));
    }
}

int dequeuePushCostly(QueuePushCostly* q) {
    if (isEmpty(q->stack1)) {
        printf("Queue is empty\n");
        return -1;
    }
    return pop(q->stack1);
}

typedef struct {
    Stack *stack1, *stack2;
} QueuePopCostly;

QueuePopCostly* createQueuePopCostly(int capacity) {
    QueuePopCostly* q = (QueuePopCostly*)malloc(sizeof(QueuePopCostly));
    q->stack1 = createStack(capacity);
    q->stack2 = createStack(capacity);
    return q;
}

void enqueuePopCostly(QueuePopCostly* q, int item) {
    push(q->stack1, item);
}

int dequeuePopCostly(QueuePopCostly* q) {
    if (isEmpty(q->stack1) && isEmpty(q->stack2)) {
        printf("Queue is empty\n");
        return -1;
    }

    if (isEmpty(q->stack2)) {
        while (!isEmpty(q->stack1)) {
            push(q->stack2, pop(q->stack1));
        }
    }

    return pop(q->stack2);
}

int main() {
    printf("=== Method 1: Push costly ===\n");
    QueuePushCostly* q1 = createQueuePushCostly(10);
    enqueuePushCostly(q1, 10);
    enqueuePushCostly(q1, 20);
    enqueuePushCostly(q1, 30);
    printf("Dequeued: %d\n", dequeuePushCostly(q1));
    printf("Dequeued: %d\n", dequeuePushCostly(q1));

    printf("\n=== Method 2: Pop costly ===\n");
    QueuePopCostly* q2 = createQueuePopCostly(10);
    enqueuePopCostly(q2, 10);
    enqueuePopCostly(q2, 20);
    enqueuePopCostly(q2, 30);
    printf("Dequeued: %d\n", dequeuePopCostly(q2));
    printf("Dequeued: %d\n", dequeuePopCostly(q2));

    return 0;
}
