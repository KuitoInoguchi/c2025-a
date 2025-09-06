#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

bool is_prime(const int n) {
    if (n <= 1) {
        return false;
    }
    if (n == 2) {
        return true;
    }
    if (n % 2 == 0) {
        return false;
    }
    const int bound = (int)sqrt(n);
    for (int i = 3; i <= bound; i += 2) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    time_t start_time = clock();
    for (int i = 2; i <= 1000; i++) {
        if (is_prime(i)) {
            printf("%d ", i);
        }
    }
    time_t end_time = clock();
    double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("\nCalculation time: %lf seconds.\n", elapsed_time);

    return 0;
}