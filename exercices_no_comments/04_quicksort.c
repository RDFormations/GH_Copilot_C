#include <stdio.h>



void insertion_sort(int arr[], int low, int high) {
    
}




int median_of_three(int arr[], int low, int high) {
    
    return 0;
}




int partition(int arr[], int low, int high) {
    
    return 0;
}




void quicksort(int arr[], int low, int high) {
    
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
