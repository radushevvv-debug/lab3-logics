#include <stdio.h>
#include <stdlib.h>

#define NAME_LENGTH 100

typedef struct Node {
    char name[NAME_LENGTH];
    struct Node *next;
} Node;

typedef struct Stack {
    Node *top;
} Stack;

void init_stack(Stack *stack)
{
    stack->top = NULL;
}

void push(Stack *stack, const char *name)
{
    Node *node = malloc(sizeof(*node));

    if (node == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    snprintf(node->name, sizeof(node->name), "%s", name);
    node->next = stack->top;
    stack->top = node;
}

void print_stack(const Stack *stack)
{
    const Node *current = stack->top;

    while (current != NULL) {
        printf("%s\n", current->name);
        current = current->next;
    }
}

void clear_stack(Stack *stack)
{
    while (stack->top != NULL) {
        Node *next = stack->top->next;
        free(stack->top);
        stack->top = next;
    }
}

int main(void)
{
    Stack stack;
    init_stack(&stack);

    push(&stack, "Document A");
    push(&stack, "Document B");
    push(&stack, "Document C");

    printf("Stack from top to bottom:\n");
    print_stack(&stack);

    clear_stack(&stack);

    return 0;
}