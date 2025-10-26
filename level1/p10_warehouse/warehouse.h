//
// Created by upsem on 2025/10/26.
//
#ifndef C2025_CHALLENGE_WAREHOUSE_H
#define C2025_CHALLENGE_WAREHOUSE_H
#define MAX_NAME_LENGTH 100
#define BUFFER_LINE_LENGTH 1024
#include <stdbool.h>
typedef struct {
    char name[MAX_NAME_LENGTH];
    int quantity;
} Item;
typedef struct {
    Item* items; // an array of items (which is actually a pointer to the first element)
    int counter;
    int capacity;
} Inventory;
void warehouse();
void new_item(Item newItem);
void load_inventory_from_file();
void save_inventory_to_file();
void print_inventory();
void guided_add();
void save_and_exit();
void stock_in(Item item_to_add);
void stock_out(Item item_to_take);
void guided_out();
bool menu(void);
void test01();
void test02();
void test03();
#endif //C2025_CHALLENGE_WAREHOUSE_H