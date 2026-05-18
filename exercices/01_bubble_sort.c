#include <stdio.h>

// TODO: Implement bubble_sort
// implement the bubble sort algorithm
void bubble_sort(int arr[], int size) {

	int temp;
	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - i - 1; j++) {
			if (arr[j] > arr[j + 1]) {
				// swap arr[j] and arr[j + 1]
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
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

