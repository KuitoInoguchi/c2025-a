//
// Created by upsem on 2025/11/10.
//

#ifndef C2025_CHALLENGE_HEADER_H
#define C2025_CHALLENGE_HEADER_H
#define SIZE 15
#define PLAYER 0
#define AI 1
#define EMPTY (-1)
#define SEARCH_DEPTH 3
typedef struct {
    int score;
    int x;
    int y;
} Move;
Move get_best_move(int board[SIZE][SIZE]);
int minimax_alpha_beta(int board[SIZE][SIZE], int depth, int alpha, int beta, int is_Max);
#endif //C2025_CHALLENGE_HEADER_H