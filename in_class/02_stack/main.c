//
// Created by upsem on 2025/9/15.
//

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* data;
    int capacity;
    int count;
    int top;
} Stack;

Stack* stack(int size) {
    Stack* s = malloc(sizeof(Stack));
    s -> data = malloc(size * sizeof(int));
    s -> capacity = size;
    s -> count = 0;
    s -> top = 0;
    return s;
}

void de_stack(Stack* s) {
    free(s -> data);
    s -> data = NULL;
    free(s);
    s = NULL;
    printf("STACK DESTRUCTED.\n");
}

void push(Stack* s, int n) {
    s -> data[s -> top++] = n;
    s -> count++;
}

int pop(Stack* s) {
    s -> count--;
    return s -> data[--s -> top];
}

_Bool empty(Stack* s) {
    return s -> top == 0;
}

_Bool full(Stack* s) {
    return s -> top == s -> capacity;
}

void test_case1(void) {
    Stack* s1 = stack(2);
    Stack* s2 = stack(2);

    if (empty(s1)) {
        printf("s1 is now empty.\n");
    }
    if (empty(s2)) {
        printf("s2 is now empty.\n");
    }

    push(s1, 1);
    push(s1, 3);
    push(s2, 2);
    push(s2, 4);

    if (full(s1)) {
        printf("s1 is now full.\n");
    }
    if (full(s2)) {
        printf("s2 is now full.\n");
    }

    int x1 = pop(s1);
    int x2 = pop(s1);
    int x3 = pop(s2);
    int x4 = pop(s2);

    printf("%d %d %d %d\n", x1, x2, x3, x4);

    if (empty(s1)) {
        printf("s1 is now empty.\n");
    }
    if (empty(s2)) {
        printf("s2 is now empty.\n");
    }

    de_stack(s1);
    de_stack(s2);
}

int rev_pol(char op);

int main() {
    // test_case1();

    return 0;
}

int rev_pol(char op) {
    int res_1 = 0;
    int res_2 = 1;
    Stack* workplace = stack(1000);
    // Stack* storeplace = stack(1000);
    while (op != '\n') {
        if (isdigit(op)) {
            push(workplace, op - '0');
        }
        else {
            while (!empty(workplace)) {
                int temp2= pop(workplace);
                int temp1 = pop(workplace);
                switch (op) {
                    case '+':
                        res_1 = temp + pop(workplace);
                        break;
                    case '-':
                        res_1 = temp + pop(workplace);
                        break;
                    case '*':
                        res_2 = temp;
                        break;
                    case '/':
                        break;
                    default:
                        break;
                }
            }
            if (op == '+') {
                push(workplace, res_1);
            }
            else if (op == '-') {
                push(workplace, res_2);
            }
        }
    }
    return pop(workplace);
}
