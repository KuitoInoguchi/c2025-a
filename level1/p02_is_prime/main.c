#include <stdio.h>
#include <math.h>
#include <stdbool.h>

bool is_prime(const int n) {
    if (n <= 1) {
        return false;
    }
    const int bound = (int)sqrt(n);
    for (int i = 2; i <= bound; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

int main0() {
    int n = 0;
    scanf("%d", &n);
    if (is_prime(n)) {
        printf("yes");
    }
    else {
        printf("no");
    }
    return 0;
}