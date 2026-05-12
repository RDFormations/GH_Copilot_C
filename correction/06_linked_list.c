#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *data;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    int size;
} LinkedList;

int add_node(LinkedList *list, void *data, size_t data_size) {
    Node *new_node = malloc(sizeof(Node));
    if (new_node == NULL)
        return -1;
    new_node->data = malloc(data_size + 1);
    if (new_node->data == NULL) {
        free(new_node);
        return -1;
    }
    memcpy(new_node->data, data, data_size);
    new_node->data[data_size] = '\0';
    new_node->next = list->head;
    list->head = new_node;
    list->size++;
    return 0;
}

/**
 * WHAT: Create a deep copy of a linked list
 * HOW: Iterative traversal with allocation of new nodes
 * CONSTRAINTS:
 *   - Returns NULL if source list is NULL or on malloc failure
 *   - The caller is responsible for freeing the copy with free_list()
 *   - Data (char*) is duplicated with strdup
 */
Node *deep_copy_list(const Node *head) {
    if (head == NULL)
        return NULL;

    Node *new_head = malloc(sizeof(Node));
    if (new_head == NULL)
        return NULL;
    new_head->data = strdup(head->data);
    if (new_head->data == NULL) {
        free(new_head);
        return NULL;
    }

    Node *current_copy = new_head;
    const Node *current_src = head->next;

    while (current_src != NULL) {
        Node *new_node = malloc(sizeof(Node));
        if (new_node == NULL)
            return new_head;
        new_node->data = strdup(current_src->data);
        if (new_node->data == NULL) {
            free(new_node);
            return new_head;
        }
        new_node->next = NULL;
        current_copy->next = new_node;
        current_copy = new_node;
        current_src = current_src->next;
    }
    current_copy->next = NULL;
    return new_head;
}

void free_list(Node *head) {
    while (head != NULL) {
        Node *tmp = head;
        head = head->next;
        free(tmp->data);
        free(tmp);
    }
}

void print_list(const Node *head) {
    const Node *current = head;
    while (current != NULL) {
        printf("[%s] -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

int main(void) {
    LinkedList list = {.head = NULL, .size = 0};

    add_node(&list, "World", 5);
    add_node(&list, "Hello", 5);
    add_node(&list, "Copilot", 7);

    printf("Liste originale (%d elements) :\n", list.size);
    print_list(list.head);

    printf("\nCopie profonde :\n");
    Node *copy = deep_copy_list(list.head);
    print_list(copy);

    printf("\nModification de la copie (premier element -> 'MODIFIED') :\n");
    free(copy->data);
    copy->data = strdup("MODIFIED");
    printf("Copie  : ");
    print_list(copy);
    printf("Origin : ");
    print_list(list.head);

    free_list(list.head);
    free_list(copy);

    return 0;
}
