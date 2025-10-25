//
// Created by upsem on 2025/10/25.
//

#ifndef C2025_CHALLENGE_PUSH_BOXES_H
#define C2025_CHALLENGE_PUSH_BOXES_H
#define HEIGHT 10
#define WIDTH 10
#define MAX_BOXES 5
#define MAX_TARGETS 5
enum directions {UP, DOWN, LEFT, RIGHT};
enum things {PLAYER, BOX};
enum type_of_move {PUSH, NO_PUSH};
typedef struct {
    int x;
    int y;
} Point;
typedef struct {
    char map[HEIGHT][WIDTH];
    Point player;
    Point prev_player;
    Point boxes[MAX_BOXES];
    Point prev_box;
    Point targets[MAX_TARGETS];
    int num_boxes;
    int num_targets;
    int remaining_targets;
    int steps;
    int box_to_push; // the index of the box to push
    enum type_of_move move_type;
} GameState;
void load_level(int level_number);
void print_the_map();
int get_input();
int which_box(int x, int y);
void move_the(enum things object, enum directions dir);
void save_previous_locations(enum things object);
int is_in_target(Point object);
void update_map(enum type_of_move move_type);
void process_move(int direction);
int is_level_won();
int select_game_level();
void sokoban_game();
#endif //C2025_CHALLENGE_PUSH_BOXES_H