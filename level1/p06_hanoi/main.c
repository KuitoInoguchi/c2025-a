#include <stdio.h>
#include "hanoi.h"

int main0() {
    int n = 0;
    scanf("%d", &n);
    hanoi(n, 'A', 'B', 'C');

    return 0;
}