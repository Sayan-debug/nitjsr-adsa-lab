#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct CircularQueueArray {
    int* arr;
    int front, rear, size, capacity;
} CircularQueueArray;

CircularQueueArray* createCircularQueueArray(int c) {
    CircularQueueArray* queue = (CircularQueueArray*)malloc(sizeof(CircularQueueArray));
    queue->capacity = c;
    queue->arr = (int*)malloc(queue->capacity * sizeof(int));
    queue->front = queue->rear = -1;
    queue->size = 0;
    return queue;
}

int isFull(CircularQueueArray* queue) {
    return queue->size == queue->capacity;
}

int isEmpty(CircularQueueArray* queue) {
    return queue->size == 0;
}

void enqueue(CircularQueueArray* queue, int val) {
    if (isFull(queue)) {
        printf("Queue is full\n");
        return;
    }
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->arr[queue->rear] = val;
    if (queue->front == -1) queue->front = queue->rear;
    queue->size++;
}

void dequeue(CircularQueueArray* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty\n");
        return;
    }
    printf("Dequeued: %d\n", queue->arr[queue->front]);
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
    if (queue->size == 0) queue->front = queue->rear = -1;
}

void display(CircularQueueArray* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty\n");
        return;
    }
    printf("Queue: ");
    for (int i = 0; i < queue->size; i++) {
        printf("%d ", queue->arr[(queue->front + i) % queue->capacity]);
    }
    printf("\n");
}

typedef struct CircularQueueLL {
    Node* front;
    Node* rear;
} CircularQueueLL;

CircularQueueLL* createCircularQueueLL() {
    CircularQueueLL* queue = (CircularQueueLL*)malloc(sizeof(CircularQueueLL));
    queue->front = queue->rear = NULL;
    return queue;
}

int isEmptyLL(CircularQueueLL* queue) {
    return queue->front == NULL;
}

void enqueueLL(CircularQueueLL* queue, int val) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = val;
    if (isEmptyLL(queue)) {
        queue->front = queue->rear = newNode;
        queue->rear->next = queue->front;  // circular link
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
        queue->rear->next = queue->front;
    }
}

void dequeueLL(CircularQueueLL* queue) {
    if (isEmptyLL(queue)) {
        printf("Queue is empty\n");
        return;
    }
    if (queue->front == queue->rear) { // only one element
        printf("Dequeued: %d\n", queue->front->data);
        free(queue->front);
        queue->front = queue->rear = NULL;
    } else {
        Node* temp = queue->front;
        printf("Dequeued: %d\n", queue->front->data);
        queue->front = queue->front->next;
        queue->rear->next = queue->front;
        free(temp);
    }
}

void displayLL(CircularQueueLL* queue) {
    if (isEmptyLL(queue)) {
        printf("Queue is empty\n");
        return;
    }
    printf("Queue: ");
    Node* temp = queue->front;
    do {
        printf("%d ", temp->data);
        temp = temp->next;
    } while (temp != queue->front);
    printf("\n");
}

int main() {

    int choice,n;
    printf("Enter the size of queue: ");
    scanf("%d",&n);
    CircularQueueArray* q1 = createCircularQueueArray(n);
    printf("Circular Queue using Array:\n");
    
    while(1){
         printf("1.Enqueue\n2.Dequeue\n3.Display\n4.Exit\n");
         int choice;
         printf("Enter your choice : ");
         scanf("%d",&choice);
         switch(choice){
             case 1: int n;
                     printf("Enter the number to insert :");
                     scanf("%d",&n);
                     enqueue(q1,n);
                     break;
             case 2: dequeue(q1);
                     break;
             case 3: display(q1);
                     break;
             case 4: printf("---Exiting---\n");
                     free(q1->arr);
                     free(q1);
                     exit(0);
                     break;
             case 5: printf("\nInvalid choice\n");
         
         }
    }
    //CircularQueueArray* q1 = createCircularQueueArray(5);
    //enqueue(q1, 10);
    //enqueue(q1, 20);
    //enqueue(q1, 30);
    //display(q1);
    //dequeue(q1);
    //display(q1);

    //printf("\nCircular Queue using Linked List:\n");
    //CircularQueueLL* q2 = createCircularQueueLL();
    //enqueueLL(q2, 100);
    //enqueueLL(q2, 200);
    //enqueueLL(q2, 300);
    //displayLL(q2);
    //dequeueLL(q2);
    //displayLL(q2);

    // Free allocated memory

    return 0;
}
