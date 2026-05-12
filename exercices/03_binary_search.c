#include <stdio.h>
#include <assert.h>

// TODO: Implement binary_search
/**
 * WHAT: Search for an element in a sorted array
 * HOW: Uses binary search (dichotomy)
 * CONSTRAINTS:
 *   - The array must be sorted in ascending order
 *   - Returns the element's index or -1 if not found
 *   - Works for arrays up to INT_MAX elements
 */
int binary_search(const int arr[], int size, int target) {
    // Use Copilot to generate the implementation
    return -1;
}

void test_binary_search_found(void) {
    int arr[] = {1, 3, 5, 7, 9, 11};
    assert(binary_search(arr, 6, 7) == 3);
    printf("[PASS] test_binary_search_found\n");
}

void test_binary_search_not_found(void) {
    int arr[] = {1, 3, 5, 7, 9, 11};
    assert(binary_search(arr, 6, 4) == -1);
    printf("[PASS] test_binary_search_not_found\n");
}

void test_binary_search_first_element(void) {
    int arr[] = {1, 3, 5, 7, 9, 11};
    assert(binary_search(arr, 6, 1) == 0);
    printf("[PASS] test_binary_search_first_element\n");
}

void test_binary_search_last_element(void) {
    int arr[] = {1, 3, 5, 7, 9, 11};
    assert(binary_search(arr, 6, 11) == 5);
    printf("[PASS] test_binary_search_last_element\n");
}

int main(void) {
    test_binary_search_found();
    test_binary_search_not_found();
    test_binary_search_first_element();
    test_binary_search_last_element();

    printf("\nAll tests passed!\n");

    int arr[] = {2, 5, 8, 12, 16, 23, 38, 45, 56, 72, 91};
    int size = sizeof(arr) / sizeof(arr[0]);
    int target = 23;

    int result = binary_search(arr, size, target);
    if (result != -1)
        printf("Element %d found at index %d\n", target, result);
    else
        printf("Element %d not found\n", target);

    return 0;
}
