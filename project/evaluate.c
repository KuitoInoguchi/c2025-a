//
// Created by upsem on 2025/11/10.
//

#include "evaluate.h"
#include <stdbool.h>
#include "general_header.h"

// extern int board[SIZE][SIZE];

// is a coordinate in the board (valid)?
int is_valid(int r, int c) {
    return r >= 0 && r < SIZE && c >= 0 && c < SIZE;
}

int get_pattern_score(int count, int open_ends) {
    if (count >= 5) return SCORE_FIVE;
    if (count == 4) {
        if (open_ends == 2) return SCORE_LIVE_FOUR;
        if (open_ends == 1) return SCORE_BLOCKED_FOUR;
        return 0;
    }
    if (count == 3) {
        if (open_ends == 2) return SCORE_LIVE_THREE;
        if (open_ends == 1) return SCORE_BLOCKED_THREE;
        return 0;
    }
    if (count == 2) {
        if (open_ends == 2) return SCORE_LIVE_TWO;
        if (open_ends == 1) return SCORE_BLOCKED_TWO;
        return 0;
    }

    return 0;
}
// color: same player
// dr = 0, dc = 1: vertically count
// dr = 1, dc = 0: horizontally count
// dr = 1; dc = 1: top left to bottom right
// dr = 1, dc = -1: top right to bottom left
// (r, c): where to start counting
int evaluate_direction(const int r, const int c, const int dr, const int dc, const int color, const int board[SIZE][SIZE]) {
    if (is_valid(r - dr, c - dc) && board[r - dr][c - dc] == color) {
        return 0;
    }

    int count = 0;
    int open_ends = 0;

    if (is_valid(r - dr, c - dc) && board[r - dr][c - dc] == EMPTY) {
        open_ends++;
    }

    int tr = r;
    int tc = c;
    while (is_valid(tr, tc) && board[tr][tc] == color) {
        count++;
        tr += dr;
        tc += dc;
    }
    if (is_valid(tr, tc) && board[tr][tc] == EMPTY) {
        open_ends++;
    }

    return get_pattern_score(count, open_ends);
}

int evaluate_board(int board[SIZE][SIZE]) {
    int ai_score = 0;
    int player_score = 0;

    for (int r = 0; r < SIZE; r++) {
        for (int c = 0; c < SIZE; c++) {
            int cell = board[r][c];

            if (cell == EMPTY) continue;
            int score = 0;
            // check current point for four directions:
            score += evaluate_direction(r, c, 0, 1, cell, board);
            score += evaluate_direction(r, c, 1, 0, cell, board);
            score += evaluate_direction(r, c, 1, 1, cell, board);
            score += evaluate_direction(r, c, 1, -1, cell, board);

            if (cell == AI) {
                ai_score += score;
            }
            else if (cell == PLAYER) {
                player_score += score;
            }
        }
    }

    return ai_score - player_score;
}

int is_game_over(const int board[SIZE][SIZE]) {
    int empty_count = 0; // 0 empty places if draw

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == EMPTY) {
                empty_count++;
                continue;
            }

            if (check_five(board, i, j, 0, 1)) return 1;
            if (check_five(board, i, j, 1, 0)) return 1;
            if (check_five(board, i, j, 1, 1)) return 1;
            if (check_five(board, i, j, 1, -1)) return 1;
        }
    }

    if (empty_count == 0) return 1;
    return 0; // not over
}

int check_five(const int board[SIZE][SIZE], int r, int c, int dr, int dc) {
    int color = board[r][c];

    for (int k = 1; k < 5; k++) {
        int nr = r + dr * k;
        int nc = c + dc * k;

        if (nr < 0 || nr >= SIZE || nc < 0 || nc >= SIZE) return 0;
        if (board[nr][nc] != color) return 0;
    }

    return 1;
}