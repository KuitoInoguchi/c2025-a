//
// Created by upsem on 2025/11/10.
//

#ifndef C2025_CHALLENGE_EVALUATE_H
#define C2025_CHALLENGE_EVALUATE_H

#include <stdbool.h>
#include "general_header.h"

#define SCORE_FIVE          100000000 // 连五（胜利）
#define SCORE_LIVE_FOUR     1000000  // 活四
#define SCORE_BLOCKED_FOUR  100000   // 冲四 / 堵四
#define SCORE_LIVE_THREE    10000    // 活三
#define SCORE_BLOCKED_THREE 1000     // 眠三
#define SCORE_LIVE_TWO      100      // 活二
#define SCORE_BLOCKED_TWO   10       // 眠二
#define SCORE_LIVE_ONE      1        // 活一
#define SCORE_BLOCKED_ONE   0        // 眠一
int is_valid(int r, int c);
int get_pattern_score(int count, int open_ends);
int evaluate_direction(int r, int c, int dr, int dc, int color, const int board[SIZE][SIZE]);
int evaluate_board(int board[SIZE][SIZE]);
int check_five(const int board[SIZE][SIZE], int r, int c, int dr, int dc);
int is_game_over(const int board[SIZE][SIZE]);
#endif //C2025_CHALLENGE_EVALUATE_H