#include <stdio.h>

// Tri par insertion sur un tableau d'entiers en ordre croissant
// Complexite : O(n^2) dans le pire cas, O(n) dans le meilleur cas
// Modifie le tableau en place
void insertion_sort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
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
