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

// TODO: Implement add_node
// Add a new node at the head of the linked list
// Copy data_size bytes from data into a newly allocated node
// Returns 0 on success, -1 on allocation error
int add_node(LinkedList *list, void *data, size_t data_size) {
    // Use Copilot to generate the implementation
    return -1;
}

// TODO: Implement deep_copy_list
/**
 * WHAT: Create a deep copy of a linked list
 * HOW: Iterative traversal with allocation of new nodes
 * CONSTRAINTS:
 *   - Returns NULL if source list is NULL or on malloc failure
 *   - The caller is responsible for freeing the copy with free_list()
 *   - Data (char*) is duplicated with strdup
 */
Node *deep_copy_list(const Node *head) {
    // Use Copilot to generate the implementation
    return NULL;
}

// TODO: Implement free_list
// Free all nodes in the list and their data
void free_list(Node *head) {
    // Use Copilot to generate the implementation
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
