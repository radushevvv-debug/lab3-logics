#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LENGTH 100
#define INPUT_LENGTH 128

typedef struct Node {
    char name[NAME_LENGTH];
    int priority;
    struct Node *next;
} Node;

Node *create_node(const char *name, int priority)
{
    Node *new_node = malloc(sizeof(*new_node));

    if (new_node == NULL) {
        printf("Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    snprintf(new_node->name, NAME_LENGTH, "%s", name);
    new_node->priority = priority;
    new_node->next = NULL;

    return new_node;
}

void insert_by_priority(Node **head, const char *name, int priority)
{
    Node *new_node = create_node(name, priority);
    Node *current;

    if (*head == NULL || priority > (*head)->priority) {
        new_node->next = *head;
        *head = new_node;
        return;
    }

    current = *head;

    while (current->next != NULL &&
           current->next->priority >= priority) {
        current = current->next;
    }

    new_node->next = current->next;
    current->next = new_node;
}

Node *extract_highest(Node **head)
{
    Node *extracted;

    if (*head == NULL) {
        return NULL;
    }

    extracted = *head;
    *head = (*head)->next;
    extracted->next = NULL;

    return extracted;
}

Node *find_by_name(Node *head, const char *name)
{
    Node *current = head;

    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return current;
        }

        current = current->next;
    }

    return NULL;
}

void print_queue(const Node *head)
{
    const Node *current = head;
    int number = 1;

    if (head == NULL) {
        printf("Priority queue is empty\n");
        return;
    }

    printf("\nPriority queue:\n");

    while (current != NULL) {
        printf("%d. %s, priority: %d\n",
               number,
               current->name,
               current->priority);

        current = current->next;
        number++;
    }
}

void clear_list(Node **head)
{
    Node *current = *head;

    while (current != NULL) {
        Node *next = current->next;
        free(current);
        current = next;
    }

    *head = NULL;
}

int read_int(const char *message)
{
    char input[INPUT_LENGTH];
    char extra;
    int value;

    while (1) {
        printf("%s", message);

        if (fgets(input, sizeof(input), stdin) == NULL) {
            exit(EXIT_SUCCESS);
        }

        if (sscanf(input, " %d %c", &value, &extra) == 1) {
            return value;
        }

        printf("Enter an integer\n");
    }
}

void read_name(const char *message, char *name, size_t size)
{
    while (1) {
        printf("%s", message);

        if (fgets(name, size, stdin) == NULL) {
            exit(EXIT_SUCCESS);
        }

        name[strcspn(name, "\n")] = '\0';

        if (name[0] != '\0') {
            return;
        }

        printf("Name cannot be empty\n");
    }
}

void print_menu(void)
{
    printf("\n1. Add element\n");
    printf("2. Extract highest-priority element\n");
    printf("3. Find element\n");
    printf("4. Show priority queue\n");
    printf("0. Exit\n");
}

int main(void)
{
    Node *head = NULL;
    int choice;

    printf("Task 1. Priority queue\n");
    printf("A larger number means a higher priority\n");

    do {
        print_menu();
        choice = read_int("Choose an action: ");

        switch (choice) {
            case 1: {
                char name[NAME_LENGTH];
                int priority;

                read_name("Enter element name: ",
                          name,
                          sizeof(name));
                priority = read_int("Enter priority: ");

                insert_by_priority(&head, name, priority);
                printf("Element added\n");
                break;
            }

            case 2: {
                Node *extracted = extract_highest(&head);

                if (extracted == NULL) {
                    printf("Priority queue is empty\n");
                } else {
                    printf("Extracted: %s, priority: %d\n",
                           extracted->name,
                           extracted->priority);
                    free(extracted);
                }
                break;
            }

            case 3: {
                char name[NAME_LENGTH];
                Node *found;

                read_name("Enter name to find: ",
                          name,
                          sizeof(name));
                found = find_by_name(head, name);

                if (found == NULL) {
                    printf("Element not found\n");
                } else {
                    printf("Found: %s, priority: %d\n",
                           found->name,
                           found->priority);
                }
                break;
            }

            case 4:
                print_queue(head);
                break;

            case 0:
                printf("Program completed\n");
                break;

            default:
                printf("Unknown menu command\n");
        }
    } while (choice != 0);

    clear_list(&head);

    return 0;
}