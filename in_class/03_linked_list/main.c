//
// Created by upsem on 2025/9/22.
//
#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node* next;
} Node;

Node* node(int data);
Node* ptr_to_end(Node* h);
int find(Node* h, int data);
Node* move_player(Node* h, int steps);
int find_next(Node* h, int data);
void add_in_front(Node** h, Node* p);
void append(Node** h, Node* p);
void free_list(Node* h);
void print_list(const Node* h);
void reverse(Node** h);
void test1();
void test2();

int main0() {
    test1();
    return 0;
}

Node* node(int data) {
    Node* p = (Node*)malloc(sizeof(Node));
    p->data = data;
    p->next = NULL;
    return p;
}

Node* ptr_to_end(Node* h) {
    Node* current = h;
    while (current->next != NULL) {
        current = current->next;
    }
    return current;
}

int find(Node* h, int data) {
    Node* current = h;
    int index = 0;
    while (current != NULL) {
        if (data == current->data) {
            break;
        }
        current = current->next;
        index++;
    }
    if (current == NULL) {
        return -1;
    }
    return index;
}

Node* move_player(Node* h, int steps) {
    Node* target = h;
    for (int i = 0; i < steps; i++) {
        target = target->next;
    }
    return target;
}

int find_next(Node* h, int data) {
    static Node* starting_pos = NULL;
    if (starting_pos == NULL) {
        starting_pos = h;
    }

    int abs_index = 0;
    Node* temp = h;
    while (temp != starting_pos) {
        temp = temp->next;
        abs_index++;
    }

    Node* current = starting_pos;
    while (current != NULL) {
        if (current->data == data) {
            break;
        }
        abs_index++;
        current = current->next;
    }
    if (current == NULL) {
        return -1;
    }

    starting_pos = current->next;
    return abs_index;
}

void add_in_front(Node** h, Node* p) {
    p->next = *h;
    *h = p;
}

void append(Node** h, Node* p) {
    Node* last = ptr_to_end(*h);
    last->next = p;
}

void free_list(Node* h) {
    Node* current = h;
    Node* next = NULL;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

void print_list(const Node* h) {
    const Node* current = h;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void reverse(Node** h) {
    Node* first = NULL;
    Node* second = *h;
    first = second;
    second = second->next;
    first->next = NULL;
    do {
        Node* temp = first;
        first = second;
        second = second->next;
        first->next = temp;
    } while (second != NULL);
    *h = first;
}

void test1() {
    Node* h0 = NULL;

    Node* p1 = node(1);
    add_in_front(&h0, p1);
    print_list(h0);

    Node* p2 = node(2);
    add_in_front(&h0, p2);
    print_list(h0);

    Node* p3 = node(114514);
    add_in_front(&h0, p3);
    print_list(h0);

    Node* p4 = node(9);
    add_in_front(&h0, p4);
    print_list(h0);

    Node* p5 = node(2472847);
    append(&h0, p5);
    print_list(h0);

    Node* p6 = node(344);
    append(&h0, p6);
    print_list(h0);

    printf("%d\n", find(h0, 344));
    reverse(&h0);
    print_list(h0);

    Node* p7 = node(5);
    Node* p8 = node(5);
    Node* p9 = node(5);
    append(&h0, p7);
    append(&h0, p8);
    append(&h0, p9);
    print_list(h0);

    printf("%d\n", find_next(h0, 5));
    printf("%d\n", find_next(h0, 5));
    printf("%d\n", find_next(h0, 5));
    free_list(h0);
}