//
// Created by upsem on 2025/10/12.
//

#include "maze.h"
#include <stdio.h>
#include <conio.h>
void move_player() {
    int dir = get_direction();
    if (not_wall(dir)) {
        change_coordinate(dir);
    }
    change_maze();
}

void print_maze() {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            printf("%c", maze[i][j]);
        }
        printf("\n");
    }
}

int get_direction() {
    for (;;) {
        if (_getch() == 224) {
            switch (_getch()) {
                case 72:
                    return up;
                case 80:
                    return down;
                case 75:
                    return left;
                case 77:
                    return right;
                default:
                    ;
            }
        }
    }
}

void change_coordinate(enum directions dir) {
    save_previous_player_position();
    switch (dir) {
        case up:
            player_x--;
            break;
        case down:
            player_x++;
            break;
        case left:
            player_y--;
            break;
        case right:
            player_y++;
            break;
        default:
            ;
    }
}

int not_wall(enum directions dir) {
    switch (dir) {
        case up:
            if (maze[player_x - 1][player_y] != '#') {
                return 1;
            }
            return 0;
        case down:
            if (maze[player_x + 1][player_y] != '#') {
                return 1;
            }
            return 0;
        case left:
            if (maze[player_x][player_y - 1] != '#') {
                return 1;
            }
            return 0;
        case right:
            if (maze[player_x][player_y + 1] != '#') {
                return 1;
            }
            return 0;
        default:
            ;
    }
    return -1;
}

void check_over() {
    if (player_x == exit_x && player_y == exit_y) {
        game_over = 1;
    }
    else {
        game_over = 0;
    }
}

void change_maze() {
    maze[temp_x][temp_y] = ' ';
    maze[player_x][player_y] = '@';
}

void save_previous_player_position() {
    temp_x = player_x;
    temp_y = player_y;
}