//
// Created by upsem on 2025/10/20.
//
#include <stdlib.h>
#include "push_boxes.h"

int main() {
    sokoban_game();
    return 0;
}

void sokoban_game() {
    int choice = select_game_level();
    load_level(choice);
    while (!is_level_won()) {
        system("cls");
        print_the_map();
        int dir = get_input();
        process_move(dir);
    }
    system("cls");
    print_the_map();
}