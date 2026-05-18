#include <stdio.h>





void insertion_sort(int arr[], int n) {
    
}

void print_array(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(void) {
    int arr[] = {12, 11, 13, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Tableau avant tri : ");
    print_array(arr, n);

    insertion_sort(arr, n);

    printf("Tableau apres tri : ");
    print_array(arr, n);

    return 0;
}
