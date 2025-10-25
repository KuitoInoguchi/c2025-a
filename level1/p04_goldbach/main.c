#include <stdio.h>
#include <stdbool.h>

int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41,
    43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101};
const size_t LEN = sizeof(primes) / sizeof(int);

bool is_prime(const int n) {
    for (int i = 0; i < LEN; i++) {
        if (n == primes[i]) {
            return true;
        }
    }
    return false;
}

bool test_goldbach() {
    for (int i = 4; i <= 100; i += 2) {
        int index = 0;
        for (int j = primes[index]; index < LEN; j = primes[++index]) {
            if (is_prime(i - j)) {
                break;
            }
            if (index == LEN - 1) {
                return false;
            }
        }
    }
    return true;
}

int main0() {
    if (test_goldbach()) {
        printf("yes");
    }
    else {
        printf("no");
    }
    return 0;
}