#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct {
    int* data;
    int init;
    int last;
    int count;
    int capacity;
} Queue;

Queue* create_queue(int size) { // the "constructor"
    Queue* q = malloc(sizeof(Queue));
    q -> data = malloc(size * sizeof(int));
    q -> count = 0;
    q -> init = 0;
    q -> last = 0;
    q -> capacity = size;
    return q;
}

void destruct_queue(Queue* q) { // the "destructor"
    free(q -> data);
    q -> data = NULL;
    free(q);
    q = NULL;
    printf("QUEUE DESTRUCTED.\n");
}
void push(Queue* q, int n) {
    q -> data[q -> last++] = n;
    q -> count++;
}

int pop(Queue* q) {
    q -> count--;
    return q -> data[q -> init++];
}

bool empty(Queue* q) {
    return q -> init == q -> last;
}

bool full(Queue* q) {
    return q -> count == q -> capacity;
}

int main0() {
    Queue* q1 = create_queue(2);
    Queue* q2 = create_queue(2);

    push(q1, 1);
    push(q2, 2);
    push(q1, 3);
    push(q2, 4);

    if (full(q1)) {
        printf("q1 is now full.\n");
    }
    if (full(q2)) {
        printf("q2 is now full.\n");
    }

    int x1 = pop(q1);
    int x2 = pop(q1);
    int x3 = pop(q2);
    int x4 = pop(q2);
    printf("%d %d %d %d\n", x1, x2, x3, x4);

    if (empty(q1)) {
        printf("q1 is now empty.\n");
    }
    if (empty(q2)) {
        printf("q2 is now empty.\n");
    }

    destruct_queue(q1);
    destruct_queue(q2);

    return 0;
}