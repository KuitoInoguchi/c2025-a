#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include
#include
#include
#include
#define HEIGHT 20
#define WIDTH 20

int game_over = 0;
char maze[HEIGHT][WIDTH] = {
    "####################",
    "#@ #   #     # #  #",
    "#  # # # ### # # ##",
    "## # # # # # ###  #",
    "#  # # # # #   # ##",
    "# ## # # # #####  #",
    "#  #   #   #   # ##",
    "## ####### # # #  #",
    "#  #     # # # ## #",
    "# ## ### # # #    #",
    "#  # #   #   # # ##",
    "## # # ##### # #  #",
    "#  # #     # # ## #",
    "# ## ##### # #  # #",
    "#    #   # #   ## #",
    "#### # # # ####  ##",
    "#  # # # #    #   #",
    "# ## # # #### ### #",
    "#  #   #            ",
    "####################",
};
int player_x = 1;
int player_y = 1;
int temp_x;
int temp_y;
const int exit_x = 18;
const int exit_y = 19;
enum directions {up, down, left, right};

void game();
void move_player();
void print_maze();
int get_direction();
void change_coordinate_of_the_thing(enum directions dir, enum things thing);
int not_wall(enum directions dir);
void check_game_over();
void change_maze();
void save_previous_position(enum things thing);

int main0() {
    game();
    return 0;
}

void game() {
    while (!game_over) {
        system("cls");
        print_maze();
        move_player();
        check_game_over();
    }
    system("cls");
    print_maze();
    printf("Game over!\n");
    system("pause");
}

void move_player() {
    int dir = get_direction();
    if (not_wall(dir)) {
        change_coordinate_of_the_thing(dir, TODO);
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

void change_coordinate_of_the_thing(enum directions dir, enum things thing) {
    save_previous_position(TODO);
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

void check_game_over() {
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

void save_previous_position(enum things thing) {
    temp_x = player_x;
    temp_y = player_y;
}