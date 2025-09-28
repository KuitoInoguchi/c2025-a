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
// Node* find_node(Node* h, int data);
int find(Node* h, int data);
void add_in_front(Node** h, Node* p);
void insert(Node** h, int data, Node* p);
void append(Node** h, Node* p);
void de_node(Node* p);
void print_list(const Node* h);
void test1();

int main() {
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

// Node* find_node(Node* h, int data) {
//     Node* current = h;
//     while (current != NULL) {
//         if (data == current->data) {
//             break;
//         }
//         current = current->next;
//     }
//     return current;
// }

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

void add_in_front(Node** h, Node* p) {
    p->next = *h;
    *h = p;
}

void insert(Node** h, const int data, Node* p) {
    // Node* target = find_node(*h, data);
    Node* current = *h;
    const int index = find(*h, data);
    if (index == -1) {
        printf("FAILED!\n");
        return;
    }
    for (int i = 0; i < index; ++i) {
        current = current->next;
    }
    add_in_front(&current, p);
}

void append(Node** h, Node* p) {
    Node* last = ptr_to_end(*h);
    last->next = p;
}

void de_node(Node* p) {
    free(p);
}

void print_list(const Node* h) {
    const Node* current = h;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void test1() {
    Node* h0 = NULL;

    Node* p1 = node(1);
    // h0 = p1;
    add_in_front(&h0, p1);
    print_list(h0);

    Node* p2 = node(2);
    // p2->next = h0;
    // h0 = p2;
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

    // int index = find(h0, 2);
    // printf("%d\n", index);
    //
    // int index2 = find(h0, 3);
    // printf("%d\n", index2);

    Node* p6 = node(344);
    insert(&h0, 114514, p6);
    print_list(h0);
}