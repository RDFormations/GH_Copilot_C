#include <stdio.h>




void bubble_sort(int arr[], int size) {
    
}

void print_array(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(void) {
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int size = sizeof(arr) / sizeof(arr[0]);

    printf("Tableau avant tri : ");
    print_array(arr, size);

    bubble_sort(arr, size);

    printf("Tableau apres tri : ");
    print_array(arr, size);

    return 0;
}
