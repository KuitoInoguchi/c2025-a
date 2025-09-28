#include <stdio.h>

void hanoi(int n, char f, char a, char t) {
    if (n == 1) {
        printf("%c -> %c\n", f, t);
        return;
    }
    hanoi(n - 1, f, t, a);
    printf("%c -> %c\n", f, t);
    hanoi(n - 1, a, f, t);
}

int main() {
    int n = 0;
    scanf("%d", &n);
    hanoi(n, 'A', 'B', 'C');

    return 0;
}