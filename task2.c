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

void print_queue(const Queue *queue)
{
    const Node *current = queue->front;

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

    printf("Queue from front to rear:\n");
    print_queue(&queue);

    clear_queue(&queue);

    return 0;
}