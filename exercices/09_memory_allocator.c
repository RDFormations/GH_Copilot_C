#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define POOL_SIZE 4096

typedef struct Block {
    size_t size;
    int free;
    struct Block *next;
} Block;

static char memory_pool[POOL_SIZE];
static Block *free_list = NULL;

// TODO: Implement pool_init
// Initialize the memory pool with a single free block
// covering the entire pool (minus the Block header)
void pool_init(void) {
    // Use Copilot to generate the implementation
}

// TODO: Implement find_free_block
// This function is part of a custom memory allocator
// It searches for a free block of sufficient size in the free list
// Uses the first-fit strategy
// Splits the block if remaining space > sizeof(Block) + 8
// Returns a pointer to usable memory (after the Block header)
void *find_free_block(size_t size) {
    // Use Copilot to generate the implementation
    return NULL;
}

// TODO: Implement pool_free
// Mark the block as free
// The block header is located sizeof(Block) bytes before ptr
void pool_free(void *ptr) {
    // Use Copilot to generate the implementation
}

void pool_status(void) {
    Block *current = free_list;
    int i = 0;
    printf("=== Pool Status ===\n");
    while (current != NULL) {
        printf("  Block %d: size=%zu, %s\n", i,
               current->size, current->free ? "FREE" : "USED");
        current = current->next;
        i++;
    }
    printf("===================\n\n");
}

int main(void) {
    pool_init();
    printf("Pool initialise (%d octets)\n\n", POOL_SIZE);
    pool_status();

    printf("Allocation de 100 octets...\n");
    char *a = find_free_block(100);
    if (a) strcpy(a, "Hello from custom allocator!");
    pool_status();

    printf("Allocation de 200 octets...\n");
    char *b = find_free_block(200);
    if (b) memset(b, 'B', 200);
    pool_status();

    printf("Allocation de 50 octets...\n");
    char *c = find_free_block(50);
    if (c) strcpy(c, "Small block");
    pool_status();

    printf("Liberation du bloc de 100 octets...\n");
    pool_free(a);
    pool_status();

    printf("Contenu du bloc c : \"%s\"\n", c);

    printf("Liberation de tous les blocs...\n");
    pool_free(b);
    pool_free(c);
    pool_status();

    return 0;
}
