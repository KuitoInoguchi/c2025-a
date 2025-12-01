#include "warehouse.h"

int test() {
    warehouse();
    return 0;
}

void warehouse() {
    load_inventory_from_file();
    while (!menu());
}