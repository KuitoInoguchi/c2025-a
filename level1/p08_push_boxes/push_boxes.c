//
// Created by upsem on 2025/10/25.
//
#include "push_boxes.h"
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

GameState current_level;
void load_level(const int level_number) {
    FILE* the_maze;
    switch (level_number) {
        case 1:
            the_maze = fopen("maze_1.txt", "r");
            if (the_maze == NULL) {
                perror("Error opening file");
                exit(1);
            }
            break;
        case 2:
            the_maze = fopen("maze_2.txt", "r");
            if (the_maze == NULL) {
                perror("Error opening file");
                exit(1);
            }
            break;
        case 3:
            the_maze = fopen("maze_3.txt", "r");
            if (the_maze == NULL) {
                perror("Error opening file");
                exit(1);
            }
            break;
        default:
            return;
    }

    current_level.num_boxes = 0;
    current_level.num_targets = 0;
    current_level.steps = 0;
    current_level.box_to_push = -1;

    // reading the file line by line into current_level.map
    int row = 0;
    while (row < HEIGHT && fgets(current_level.map[row], WIDTH + 5, the_maze) != NULL) {
        current_level.map[row][strcspn(current_level.map[row], "\n")] = '\0';
        row++;
    }

    // now handle the numbers of boxes and targets
    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            switch (current_level.map[i][j]) {
                case '@':
                    current_level.player.x = i;
                    current_level.player.y = j;
                    break;
                case '$':
                    current_level.num_boxes++;
                    current_level.boxes[current_level.num_boxes - 1].x = i;
                    current_level.boxes[current_level.num_boxes - 1].y = j;
                    break;
                case '.':
                    current_level.num_targets++;
                    current_level.targets[current_level.num_targets - 1].x = i;
                    current_level.targets[current_level.num_targets - 1].y = j;
                    break;
                default:
                    ;
            }
        }
    }
    current_level.remaining_targets = current_level.num_targets;

    fclose(the_maze);
}

void print_the_map() {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            printf("%c", current_level.map[i][j]);
        }
        printf("\n");
    }
}

int get_input() {
    for (;;) {
        if (_getch() == 224) {
            switch (_getch()) {
                case 72:
                    return UP;
                case 80:
                    return DOWN;
                case 75:
                    return LEFT;
                case 77:
                    return RIGHT;
                default:
                    ;
            }
        }
    }
}

void process_move(int direction) { // does not modify the map
    int player_x = current_level.player.x;
    int player_y = current_level.player.y;
    current_level.move_type = NO_PUSH;

    int move_to_x = player_x;
    int move_to_y = player_y;
    if (direction == UP) move_to_x--;
    if (direction == DOWN) move_to_x++;
    if (direction == LEFT) move_to_y--;
    if (direction == RIGHT) move_to_y++;

    char target_tile = current_level.map[move_to_x][move_to_y];
    switch (target_tile) {
        case '#':
            break;
        case ' ':
        case '.':
            move_the(PLAYER, direction);
            current_level.steps++;
            break;
        case '$':
            // the potential push-to tile
            current_level.box_to_push = which_box(move_to_x, move_to_y);
            int beyond_x = move_to_x + (move_to_x - player_x);
            int beyond_y = move_to_y + (move_to_y - player_y);
            char beyond_tile = current_level.map[beyond_x][beyond_y];
            if (beyond_tile == ' ' || beyond_tile == '.') {
                current_level.move_type = PUSH;
                move_the(PLAYER, direction);
                move_the(BOX, direction);
                current_level.steps++;
                break;
            }
        default:
            ;
    }

    update_map(current_level.move_type);
}

void move_the(enum things object, enum directions dir) {
    save_previous_locations(object);
    switch (object) {
        case PLAYER:
            switch (dir) {
            case UP:
                    current_level.player.x--;
                    break;
            case DOWN:
                    current_level.player.x++;
                    break;
            case LEFT:
                    current_level.player.y--;
                    break;
            case RIGHT:
                    current_level.player.y++;
                    break;
            default:
                    ;
            }
            break;
        case BOX:
            switch (dir) {
            case UP:
                    current_level.boxes[current_level.box_to_push].x--;
                    break;
            case DOWN:
                    current_level.boxes[current_level.box_to_push].x++;
                    break;
            case LEFT:
                    current_level.boxes[current_level.box_to_push].y--;
                    break;
            case RIGHT:
                    current_level.boxes[current_level.box_to_push].y++;
                    break;
            default:
                    ;
            }
            break;
    }
}

int which_box(int x, int y) {
    int box_index = -1;
    for (int i = 0; i < current_level.num_boxes; i++) {
        if (current_level.boxes[i].x == x && current_level.boxes[i].y == y) {
            box_index = i;
            break;
        }
    }
    return box_index;
}

void save_previous_locations(enum things object) {
    switch (object) {
        case PLAYER:
            current_level.prev_player.x = current_level.player.x;
            current_level.prev_player.y = current_level.player.y;
            break;
        case BOX:
            current_level.prev_box.x = current_level.boxes[current_level.box_to_push].x;
            current_level.prev_box.y = current_level.boxes[current_level.box_to_push].y;
            break;
    }
}

int is_in_target(Point object) {
    for (int i = 0; i < current_level.num_targets; i++) {
        if (object.x == current_level.targets[i].x && object.y == current_level.targets[i].y) {
            return 1; // true
        }
    }
    return 0; // false
}

void update_map(enum type_of_move move_type) {
    // // new player location
    // if (!is_in_target(current_level.player)) {
    //     current_level.map[current_level.prev_player.x][current_level.prev_player.y] = ' ';
    //     current_level.map[current_level.player.x][current_level.player.y] = '@';
    // }
    // else {
    //     current_level.map[current_level.prev_player.x][current_level.prev_player.y] = '.';
    //     current_level.map[current_level.player.x][current_level.player.y] = '@';
    // }
    //
    // // new box location
    // if (!is_in_target(current_level.boxes[current_level.box_to_push])) {
    //     current_level.map[current_level.prev_box.x][current_level.prev_box.y] = '@';
    //     current_level.map[current_level.boxes[current_level.box_to_push].x][current_level.boxes[current_level.box_to_push].y] = '$';
    // }
    // else {
    //     current_level.map[current_level.prev_box.x][current_level.prev_box.y] = '@';
    //     current_level.map[current_level.boxes[current_level.box_to_push].x][current_level.boxes[current_level.box_to_push].y] = ' ';
    // }

    // switch (move_type) {
    //     case NO_PUSH:
    //         if (is_in_target(current_level.prev_player)) {
    //             current_level.map[current_level.prev_player.x][current_level.prev_player.y] = '.';
    //             current_level.map[current_level.player.x][current_level.player.y] = '@';
    //         }
    //         else {
    //             current_level.map[current_level.prev_player.x][current_level.prev_player.y] = ' ';
    //             current_level.map[current_level.player.x][current_level.player.y] = '@';
    //         }
    //     case PUSH:
    //         if (is_in_target(current_level.prev_player)) {
    //             current_level.map[current_level.prev_player.x][current_level.prev_player.y] = '.';
    //             if (is_in_target(current_level.boxes[current_level.box_to_push])) {
    //                 current_level.map[current_level.boxes[current_level.box_to_push].x][current_level.boxes[current_level.box_to_push].y] = '*';
    //             }
    //             else
    //                 current_level.map[current_level.boxes[current_level.box_to_push].x][current_level.boxes[current_level.box_to_push].y] = '$';
    //         }
    //         else {
    //             current_level.map[current_level.prev_player.x][current_level.prev_player.y] = ' ';
    //             if (is_in_target(current_level.boxes[current_level.box_to_push])) {
    //                 current_level.map[current_level.boxes[current_level.box_to_push].x][current_level.boxes[current_level.box_to_push].y] = '*';
    //                 current_level.remaining_targets--;
    //             }
    //             else
    //                 current_level.map[current_level.boxes[current_level.box_to_push].x][current_level.boxes[current_level.box_to_push].y] = '$';
    //         }
    // }

    if (is_in_target(current_level.prev_player)) {
        current_level.map[current_level.prev_player.x][current_level.prev_player.y] = '.';
    } else {
        current_level.map[current_level.prev_player.x][current_level.prev_player.y] = ' ';
    }

    if (move_type == NO_PUSH) {
        current_level.map[current_level.player.x][current_level.player.y] = '@';
    }
    else if (move_type == PUSH) {
        current_level.map[current_level.player.x][current_level.player.y] = '@';

        Point new_box_pos = current_level.boxes[current_level.box_to_push];

        if (is_in_target(new_box_pos)) {
            current_level.map[new_box_pos.x][new_box_pos.y] = '*';
            current_level.remaining_targets--;
        } else {
            current_level.map[new_box_pos.x][new_box_pos.y] = '$';
        }
    }

}

int is_level_won() {
    if (current_level.remaining_targets == 0) return 1;
    return 0;
}

int select_game_level() {
    int game_level = 0;
    for (;;) {
        printf("Enter the level you want to play (1, 2 or 3): ");
        scanf("%d", &game_level);
        if (game_level == 1 || game_level == 2 || game_level == 3) return game_level;
            printf("Invalid choice. Try again!\n");
        }
}