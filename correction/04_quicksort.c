#include <stdio.h>

// Quicksort avec pivot median de trois, partition de Lomuto
// Gere les tableaux de taille < 10 avec insertion sort
void insertion_sort(int arr[], int low, int high) {
    for (int i = low + 1; i <= high; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= low && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

int median_of_three(int arr[], int low, int high) {
    int mid = low + (high - low) / 2;
    if (arr[low] > arr[mid]) {
        int t = arr[low]; arr[low] = arr[mid]; arr[mid] = t;
    }
    if (arr[low] > arr[high]) {
        int t = arr[low]; arr[low] = arr[high]; arr[high] = t;
    }
    if (arr[mid] > arr[high]) {
        int t = arr[mid]; arr[mid] = arr[high]; arr[high] = t;
    }
    int t = arr[mid]; arr[mid] = arr[high - 1]; arr[high - 1] = t;
    return arr[high - 1];
}

int partition(int arr[], int low, int high) {
    int pivot = median_of_three(arr, low, high);
    int i = low;
    int j = high - 1;

    while (1) {
        while (arr[++i] < pivot);
        while (arr[--j] > pivot);
        if (i >= j) break;
        int t = arr[i]; arr[i] = arr[j]; arr[j] = t;
    }
    int t = arr[i]; arr[i] = arr[high - 1]; arr[high - 1] = t;
    return i;
}

void quicksort(int arr[], int low, int high) {
    if (high - low < 10) {
        insertion_sort(arr, low, high);
        return;
    }
    int pivot_idx = partition(arr, low, high);
    quicksort(arr, low, pivot_idx - 1);
    quicksort(arr, pivot_idx + 1, high);
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
