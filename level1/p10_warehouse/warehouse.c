//
// Created by upsem on 2025/10/26.
//
#include "warehouse.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Inventory Warehouse;
void test01() {
    load_inventory_from_file();
    print_inventory();
}
void test02() {
    load_inventory_from_file();
    for (;;) {
        print_inventory();
        guided_add();
    }
}

void test03() {
    load_inventory_from_file();
    for (;;) {
        print_inventory();
        guided_add();
        guided_out();
    }
}

bool menu(void) {
    int c;
    printf("Warehouse manager: Welcome!\n");
    printf("Select an option:\n");
    printf("1. Display current inventory\n2. Stock in\n3. Stock out\n4. Exit the program\n");
    scanf("%d", &c);
    int k;
    while ((k = getchar()) != '\n' && c != EOF);
    switch (c) {
        case 1:
            print_inventory();
            break;
        case 2:
            guided_add();
            break;
        case 3:
            guided_out();
            break;
        case 4:
            save_and_exit();
            return true;
        default:
            printf("Invalid choice! Try again.\n");
            break;
    }
    return false;
}

void guided_add() {
    while (1) {
        Item item_to_add;
        printf("Enter an item in the following format:\n");
        printf("{name},{quantity}\n");
        printf("e.g. thingA,55: \n");
        int result = scanf("%99[^,],%d", item_to_add.name, &item_to_add.quantity);

        if (result == 2) {
            stock_in(item_to_add);
        }
        else {
            printf("Invalid input format! Try again.\n");
            while (getchar() != '\n'){} // clear all invalid input
            continue;
        }

        printf("Add more? (Y/n) ");
        char choice;
        getchar();
        scanf(" %c", &choice);
        getchar();
        if (choice == 'n') {
            printf("Here ends the adding process.\n");
            return;
        }
    }
}

void new_item(Item newItem) {
    if (Warehouse.capacity == Warehouse.counter) {
        int newCapacity = (Warehouse.capacity == 0) ? 10 : Warehouse.capacity * 2;
        Item* newItems = realloc(Warehouse.items, newCapacity * sizeof(Item));
        if (newItems == NULL) {
            printf("Error: Memory allocation failed");
            return;
        }
        Warehouse.items = newItems;
        Warehouse.capacity = newCapacity;
    }
    Warehouse.items[Warehouse.counter] = newItem;
    Warehouse.counter++;
}

void load_inventory_from_file() {
    FILE* inventory;
    inventory = fopen("inventory.txt", "r");
    if (inventory == NULL) {
        perror("Failed to load from file");
        return;
    }

    char line[BUFFER_LINE_LENGTH];
    while (fgets(line, BUFFER_LINE_LENGTH, inventory)) {
        Item currentItem;
        int result = sscanf(line, "%99[^,],%d", currentItem.name, &currentItem.quantity);
        if (result == 2) {
            new_item(currentItem);
        }
        else {
            printf("Warning: Malformed line skipped: %s", line);
        }
    }

    fclose(inventory);
}

void save_inventory_to_file() {
    FILE* inventory;
    inventory = fopen("inventory.txt", "w");
    if (inventory == NULL) {
        perror("Failed to load from file");
        return;
    }

    for (int i = 0; i < Warehouse.counter; i++) {
        fprintf(inventory, "%s,%d\n", Warehouse.items[i].name, Warehouse.items[i].quantity);
    }
    printf("Successfully saved inventory to file.");

    fclose(inventory);
}

void print_inventory() {
    for (int i = 0; i < Warehouse.counter; i++) {
        printf("%s: %d\n", Warehouse.items[i].name, Warehouse.items[i].quantity);
    }
}

void save_and_exit() {
    save_inventory_to_file();
    printf("Bye!");
}

void stock_in(Item item_to_add) {
    for (int i = 0; i < Warehouse.counter; i++) {
        if (strcmp(Warehouse.items[i].name, item_to_add.name) == 0) {
            Warehouse.items[i].quantity += item_to_add.quantity;
            return;
        }
    }
    new_item(item_to_add);
}

void stock_out(Item item_to_take) {
    for (int i = 0; i < Warehouse.counter; i++) {
        if (strcmp(Warehouse.items[i].name, item_to_take.name) == 0) {
            if (Warehouse.items[i].quantity >= item_to_take.quantity) {
                Warehouse.items[i].quantity -= item_to_take.quantity;
                printf("Item taken\n");
                return;
            }
            else {
                printf("Too much to take.\n");
                return;
            }
        }
    }
    printf("No such item!\n");
}

void guided_out() {
    Item item_to_take;
    printf("Enter what item and how much you want to take out in the following format\n");
    printf("{name},{quantity}: ");
    scanf("%99[^,],%d", item_to_take.name, &item_to_take.quantity);
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    stock_out(item_to_take);
}