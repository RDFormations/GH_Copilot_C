#include <stdio.h>

// TODO: Implement insertion_sort for small arrays
// Tri par insertion entre les indices low et high (inclus)
void insertion_sort(int arr[], int low, int high) {
    // Use Copilot to generate the implementation
}

// TODO: Implement median_of_three
// Select the median of arr[low], arr[mid], arr[high] as pivot
// Place the pivot at arr[high-1] and return its value
int median_of_three(int arr[], int low, int high) {
    // Use Copilot to generate the implementation
    return 0;
}

// TODO: Implement partition
// Lomuto-style partition using median_of_three pivot
// Returns the final index of the pivot
int partition(int arr[], int low, int high) {
    // Use Copilot to generate the implementation
    return 0;
}

// TODO: Implement quicksort
// Quicksort with median-of-three pivot, Lomuto partition
// Handle arrays of size < 10 with insertion sort
void quicksort(int arr[], int low, int high) {
    // Use Copilot to generate the implementation
}

void print_array(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(void) {
    int arr[] = {38, 27, 43, 3, 9, 82, 10, 56, 44, 12, 64, 7, 91, 23, 15};
    int size = sizeof(arr) / sizeof(arr[0]);

    printf("Tableau avant tri : ");
    print_array(arr, size);

    quicksort(arr, 0, size - 1);

    printf("Tableau apres tri : ");
    print_array(arr, size);

    return 0;
}
