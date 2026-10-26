#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>

#define NAME_LENGTH 100
#define INPUT_LENGTH 128

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

Node *pop(Stack *stack)
{
    if (stack->top == NULL) {
        return NULL;
    }

    Node *removed = stack->top;
    stack->top = removed->next;
    removed->next = NULL;

    return removed;
}

const Node *find_by_name(const Stack *stack, const char *name)
{
    const Node *current = stack->top;

    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return current;
        }

        current = current->next;
    }

    return NULL;
}

void print_stack(const Stack *stack)
{
    const Node *current = stack->top;
    int number = 1;

    if (current == NULL) {
        printf("Stack is empty\n");
        return;
    }

    printf("\nStack from top to bottom:\n");

    while (current != NULL) {
        printf("%d. %s\n", number, current->name);
        current = current->next;
        number++;
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

int read_line(const char *message, char *buffer, size_t size)
{
    while (1) {
        printf("%s", message);
        fflush(stdout);

        if (fgets(buffer, size, stdin) == NULL) {
            return 0;
        }

        if (strchr(buffer, '\n') == NULL) {
            int ch = getchar();

            if (ch != '\n' && ch != EOF) {
                while (ch != '\n' && ch != EOF) {
                    ch = getchar();
                }

                printf("Input is too long. Maximum: %zu bytes\n",
                       size - 1);
                continue;
            }
        }

        buffer[strcspn(buffer, "\r\n")] = '\0';
        return 1;
    }
}

int read_int(const char *message, int *value)
{
    char input[INPUT_LENGTH];

    while (read_line(message, input, sizeof(input))) {
        char *end;
        long number;

        errno = 0;
        number = strtol(input, &end, 10);

        if (end != input) {
            while (isspace((unsigned char)*end)) {
                end++;
            }

            if (*end == '\0' && errno != ERANGE &&
                number >= INT_MIN && number <= INT_MAX) {
                *value = (int)number;
                return 1;
            }
        }

        printf("Enter an integer from %d to %d\n",
               INT_MIN, INT_MAX);
    }

    return 0;
}

int read_name(const char *message, char *name, size_t size)
{
    while (read_line(message, name, size)) {
        if (name[0] != '\0') {
            return 1;
        }

        printf("Name cannot be empty\n");
    }

    return 0;
}

void print_menu(void)
{
    printf("\n1. Add element\n");
    printf("2. Extract top element\n");
    printf("3. Find element\n");
    printf("4. Show stack\n");
    printf("0. Exit\n");
}

int main(void)
{
    Stack stack;
    int choice;

    init_stack(&stack);

    printf("Task 3. LIFO stack\n");
    printf("The last added element is extracted first\n");

    do {
        print_menu();

        if (!read_int("Choose an action: ", &choice)) {
            break;
        }

        switch (choice) {
            case 1: {
                char name[NAME_LENGTH];

                if (!read_name("Enter element name: ",
                               name, sizeof(name))) {
                    choice = 0;
                    break;
                }

                push(&stack, name);
                printf("Element added to the top of the stack\n");
                break;
            }

            case 2: {
                Node *removed = pop(&stack);

                if (removed == NULL) {
                    printf("Stack is empty\n");
                } else {
                    printf("Extracted: %s\n", removed->name);
                    free(removed);
                }
                break;
            }

            case 3: {
                char name[NAME_LENGTH];
                const Node *found;

                if (!read_name("Enter name to find: ",
                               name, sizeof(name))) {
                    choice = 0;
                    break;
                }

                found = find_by_name(&stack, name);

                if (found == NULL) {
                    printf("Element not found\n");
                } else {
                    printf("Element found: %s\n", found->name);
                }
                break;
            }

            case 4:
                print_stack(&stack);
                break;

            case 0:
                break;

            default:
                printf("Unknown menu command\n");
        }
    } while (choice != 0);

    clear_stack(&stack);
    printf("Program completed\n");

    return 0;
}