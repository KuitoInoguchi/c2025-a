#include <stdio.h>
#include <stdlib.h>

void move_forwards(const int ScreenWidth) {
    for (int i = 0; i < ScreenWidth; i++) {
        system("cls"); // clear the screen
        for (int j = 0; j < i; j++) {
            printf(" ");
        }
        printf("a");
    }
}

void move_backwards(const int ScreenWidth) {
    for (int i = ScreenWidth; i > 0; i--) {
        system("cls");
        for (int j = 0; j < i; j++) {
            printf(" ");
        }
        printf("a");
    }
}

int main0() {
    const int SCREEN_WIDTH = 50;
    for (;;) {
        move_forwards(SCREEN_WIDTH);
        move_backwards(SCREEN_WIDTH);
    }
    return 0;
}
