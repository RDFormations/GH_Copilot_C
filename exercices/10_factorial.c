#include <stdio.h>
#include <assert.h>

// TODO: Implement calculate_factorial
// Calculate the factorial of n (iterative approach)
// Returns -1 for negative input
// Returns 1 for n == 0 or n == 1
int calculate_factorial(int n) {
    if (n < 0) return -1;
    if (n == 0 || n == 1) return 1;

    int result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

void test_calculate_factorial(void) {
    printf("=== Tests calculate_factorial ===\n\n");

    // Test negative input
    assert(calculate_factorial(-5) == -1);
    printf("Test négative: OK\n");

    // Test base cases
    assert(calculate_factorial(0) == 1);
    printf("Test base 0: OK\n");
    assert(calculate_factorial(1) == 1);
    printf("Test base 1: OK\n");

    // Test normal cases
    assert(calculate_factorial(5) == 120);
    printf("Test 5!: OK\n");
    assert(calculate_factorial(10) == 3628800);
    printf("Test 10!: OK\n");
    assert(calculate_factorial(12) == 479001600);
    printf("Test 12!: OK\n");

    printf("\n");
}

int main(void) {
    test_calculate_factorial();

    printf("=== Calcul de factorielles ===\n\n");
    for (int i = 0; i <= 12; i++) {
        printf("  %2d! = %d\n", i, calculate_factorial(i));
    }
    return 0;
}
