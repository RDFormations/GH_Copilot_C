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
    
    return -1;
}



Node *deep_copy_list(const Node *head) {
    
    return NULL;
}



void free_list(Node *head) {
    
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
