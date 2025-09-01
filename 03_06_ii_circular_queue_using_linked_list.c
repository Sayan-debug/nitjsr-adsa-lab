#include <stdio.h>
#include <stdlib.h>
typedef struct Node {
    int data;
    struct Node* next;
} Node;
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
    CircularQueueLL* q1 = createCircularQueueLL();
    printf("Circular Queue using Linked list:\n");
    
    while(1){
         printf("1.Enqueue\n2.Dequeue\n3.Display\n4.Exit\n");
         int choice;
         printf("Enter your choice : ");
         scanf("%d",&choice);
         switch(choice){
             case 1: int n;
                     printf("Enter the number to insert :");
                     scanf("%d",&n);
                     enqueueLL(q1, n);
                     break;
             case 2: dequeueLL(q1);
                     break;
             case 3: displayLL(q1);
                     break;
             case 4: printf("---Exiting---\n");
                     free(q1);
                     exit(0);
                     break;
             case 5: printf("\nInvalid choice\n");
         
         }
    }
    
   return 0;
}
