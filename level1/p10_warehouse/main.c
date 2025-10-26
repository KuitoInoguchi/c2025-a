#include "warehouse.h"

int main() {
    warehouse();
    return 0;
}

void warehouse() {
    load_inventory_from_file();
    while (!menu());
}