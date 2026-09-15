#include <stdio.h>

// TODO: Implement bubble_sort
// Tri a bulles sur un tableau d'entiers en ordre croissant
// Modifie le tableau en place
void bubble_sort(int arr[], int size) {
    // Use Copilot to generate the implementation
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
