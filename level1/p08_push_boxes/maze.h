//
// Created by upsem on 2025/10/12.
//

#ifndef C2025_CHALLENGE_MAZE_H
#define C2025_CHALLENGE_MAZE_H
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
void change_coordinate(enum directions dir);
int not_wall(enum directions dir);
void check_over();
void change_maze();
void save_previous_player_position();
#endif //C2025_CHALLENGE_MAZE_H