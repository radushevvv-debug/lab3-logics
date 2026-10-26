#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LENGTH 100
#define INPUT_LENGTH 128

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

int is_empty(const Queue *queue)
{
    return queue->front == NULL;
}

Node *create_node(const char *name)
{
    Node *new_node = malloc(sizeof(*new_node));

    if (new_node == NULL) {
        printf("Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    snprintf(new_node->name, NAME_LENGTH, "%s", name);
    new_node->next = NULL;

    return new_node;
}

void enqueue(Queue *queue, const char *name)
{
    Node *new_node = create_node(name);

    if (is_empty(queue)) {
        queue->front = new_node;
        queue->rear = new_node;
        return;
    }

    queue->rear->next = new_node;
    queue->rear = new_node;
}

Node *dequeue(Queue *queue)
{
    Node *removed;

    if (is_empty(queue)) {
        return NULL;
    }

    removed = queue->front;
    queue->front = queue->front->next;
    removed->next = NULL;

    if (queue->front == NULL) {
        queue->rear = NULL;
    }

    return removed;
}

Node *find_by_name(const Queue *queue, const char *name)
{
    Node *current = queue->front;

    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return current;
        }

        current = current->next;
    }

    return NULL;
}

void print_queue(const Queue *queue)
{
    const Node *current = queue->front;
    int number = 1;

    if (is_empty(queue)) {
        printf("Queue is empty\n");
        return;
    }

    printf("\nQueue from front to rear:\n");

    while (current != NULL) {
        printf("%d. %s\n", number, current->name);
        current = current->next;
        number++;
    }
}

void clear_queue(Queue *queue)
{
    Node *current = queue->front;

    while (current != NULL) {
        Node *next = current->next;
        free(current);
        current = next;
    }

    queue->front = NULL;
    queue->rear = NULL;
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
    printf("2. Extract first element\n");
    printf("3. Find element\n");
    printf("4. Show queue\n");
    printf("0. Exit\n");
}

int main(void)
{
    Queue queue;
    int choice;

    init_queue(&queue);

    printf("Task 2. FIFO queue\n");
    printf("The first added element is extracted first\n");

    do {
        print_menu();
        choice = read_int("Choose an action: ");

        switch (choice) {
            case 1: {
                char name[NAME_LENGTH];

                read_name("Enter element name: ",
                          name,
                          sizeof(name));

                enqueue(&queue, name);
                printf("Element added to the end of the queue\n");
                break;
            }

            case 2: {
                Node *removed = dequeue(&queue);

                if (removed == NULL) {
                    printf("Queue is empty\n");
                } else {
                    printf("Extracted: %s\n", removed->name);
                    free(removed);
                }
                break;
            }

            case 3: {
                char name[NAME_LENGTH];
                Node *found;

                read_name("Enter name to find: ",
                          name,
                          sizeof(name));

                found = find_by_name(&queue, name);

                if (found == NULL) {
                    printf("Element not found\n");
                } else {
                    printf("Element found: %s\n", found->name);
                }
                break;
            }

            case 4:
                print_queue(&queue);
                break;

            case 0:
                printf("Program completed\n");
                break;

            default:
                printf("Unknown menu command\n");
        }
    } while (choice != 0);

    clear_queue(&queue);

    return 0;
}