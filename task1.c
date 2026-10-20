#include <stdio.h>
#include <stdlib.h>

#define NAME_LENGTH 100

typedef struct Node {
    char name[NAME_LENGTH];
    int priority;
    struct Node *next;
} Node;

Node *create_node(const char *name, int priority)
{
    Node *node = malloc(sizeof(*node));

    if (node == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    snprintf(node->name, sizeof(node->name), "%s", name);
    node->priority = priority;
    node->next = NULL;

    return node;
}

int main(void)
{
    Node *head = create_node("Document A", 2);

    printf("Created: %s, priority: %d\n",
           head->name, head->priority);

    free(head);

    return 0;
}