#include <stdio.h>

#define NAME_LENGTH 100
ы
typedef struct Node {
    char name[NAME_LENGTH];
    struct Node *next;
} Node;

typedef struct Queue {
    Node *front;
    Node *rear;
} Queue;

void init_queue(Queue *queue)
{
    queue->front = NULL;
    queue->rear = NULL;
}

int main(void)
{
    Queue queue;

    init_queue(&queue);

    printf("Task 2. FIFO queue\n");
    printf("Queue initialized: empty\n");

    return 0;
}