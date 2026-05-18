int calculate_factorial(int n) {
	if (n < 0) {
		return -1; // Return -1 for negative numbers
	} else if (n == 0 || n == 1) {
		return 1; // Factorial of 0 and 1 is 1
	} else {
		return n * calculate_factorial(n - 1); // Recursive call
	}
}


// Trier un tableau d'entiers en ordre croissant avec un quick sort
void quick_sort(int arr[], int low, int high) {
	if (low < high) {
		int pi = partition(arr, low, high); // Partitioning index

		// Recursively sort elements before and after partition
		quick_sort(arr, low, pi - 1);
		quick_sort(arr, pi + 1, high);
	}
}


typedef struct {
    char name[50];
    int age;
    float salary;
} Employee;

int compare_employees(const void *a, const void *b) {
	Employee *empA = (Employee *)a;
	Employee *empB = (Employee *)b;

	// Compare by age
	if (empA->age < empB->age) {
		return -1;
	} else if (empA->age > empB->age) {
		return 1;
	} else {
		return 0; // Ages are equal
	}
}