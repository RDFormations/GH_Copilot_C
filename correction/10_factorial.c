#include <stdio.h>

int calculate_factorial(int n) {
    if (n < 0)
        return -1;
    if (n == 0 || n == 1)
        return 1;
    int result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

int main(void) {
    printf("=== Calcul de factorielles ===\n\n");
    for (int i = 0; i <= 12; i++) {
        printf("  %2d! = %d\n", i, calculate_factorial(i));
    }
    return 0;
}
