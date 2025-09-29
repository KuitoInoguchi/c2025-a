//
// Created by upsem on 2025/9/29.
//
#include <stdio.h>
#include "hanoi.h"
void hanoi(int n, char f, char a, char t) {
    if (n == 1) {
        printf("%c -> %c\n", f, t);
        return;
    }
    hanoi(n - 1, f, t, a);
    printf("%c -> %c\n", f, t);
    hanoi(n - 1, a, f, t);
}