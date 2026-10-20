#include <stdio.h>
#include <stdlib.h>

#define NAME_LENGTH 100

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

void enqueue(Queue *queue, const char *name)
{
    Node *node = malloc(sizeof(*node));

    if (node == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    snprintf(node->name, sizeof(node->name), "%s", name);
    node->next = NULL;

    if (queue->rear == NULL) {
        queue->front = node;
    } else {
        queue->rear->next = node;
    }

    queue->rear = node;
}

Node *dequeue(Queue *queue)
{
    if (queue->front == NULL) {
        return NULL;
    }

    Node *removed = queue->front;
    queue->front = removed->next;

    if (queue->front == NULL) {
        queue->rear = NULL;
    }

    removed->next = NULL;
    return removed;
}

void print_queue(const Queue *queue)
{
    const Node *current = queue->front;

    if (current == NULL) {
        printf("Queue is empty\n");
        return;
    }

    while (current != NULL) {
        printf("%s\n", current->name);
        current = current->next;
    }
}

void clear_queue(Queue *queue)
{
    while (queue->front != NULL) {
        Node *next = queue->front->next;
        free(queue->front);
        queue->front = next;
    }

    queue->rear = NULL;
}

int main(void)
{
    Queue queue;
    init_queue(&queue);

    enqueue(&queue, "Document A");
    enqueue(&queue, "Document B");
    enqueue(&queue, "Document C");

    printf("Queue before extraction:\n");
    print_queue(&queue);

    Node *removed = dequeue(&queue);

    if (removed != NULL) {
        printf("\nExtracted: %s\n", removed->name);
        free(removed);
    }

    printf("\nQueue after extraction:\n");
    print_queue(&queue);

    clear_queue(&queue);

    return 0;
}