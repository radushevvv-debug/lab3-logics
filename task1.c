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

void insert_by_priority(Node **head, const char *name, int priority)
{
    Node *node = create_node(name, priority);

    if (*head == NULL || priority > (*head)->priority) {
        node->next = *head;
        *head = node;
        return;
    }

    Node *current = *head;

    while (current->next != NULL &&
           current->next->priority >= priority) {
        current = current->next;
    }

    node->next = current->next;
    current->next = node;
}

void print_queue(const Node *head)
{
    const Node *current = head;

    while (current != NULL) {
        printf("%s (priority %d)\n",
               current->name, current->priority);
        current = current->next;
    }
}

void clear_queue(Node **head)
{
    while (*head != NULL) {
        Node *next = (*head)->next;
        free(*head);
        *head = next;
    }
}

int main(void)
{
    Node *head = NULL;

    insert_by_priority(&head, "Document A", 2);
    insert_by_priority(&head, "Document B", 5);
    insert_by_priority(&head, "Document C", 3);

    printf("Priority queue:\n");
    print_queue(head);

    clear_queue(&head);

    return 0;
}