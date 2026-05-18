#include <stdio.h>





int calculate_factorial(int n) {
    
    return -1;
}

int main(void) {
    printf("=== Calcul de factorielles ===\n\n");
    for (int i = 0; i <= 12; i++) {
        printf("  %2d! = %d\n", i, calculate_factorial(i));
    }
    return 0;
}
