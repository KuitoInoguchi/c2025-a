//
// Created by upsem on 2025/11/3.
//

// work to do
// 1. depth-first search
// 2. evaluation function
// 3. minimax
// 4. alpha-beta pruning

#include <limits.h>
#include <stdio.h>
#include "evaluate.h"
#include "search.h"


int minimax_alpha_beta(int board[SIZE][SIZE], int depth, int alpha, int beta, int is_Max) {
    if (depth == 0 || is_game_over(board)){
        return evaluate_board(board);
    }

    if (is_Max) {
        int max_eval = INT_MIN;

        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = AI;
                    int eval = minimax_alpha_beta(board, depth - 1, alpha, beta, 0);
                    board[i][j] = EMPTY;

                    if (eval > max_eval) {
                        max_eval = eval;
                    }
                    if (eval > alpha) {
                        alpha = eval;
                    }
                    if (beta <= alpha) break;
                }
            }
            if (beta <= alpha) break;
        }

        return max_eval;
    }

    else {
        int min_eval = INT_MAX;

        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = PLAYER;
                    int eval = minimax_alpha_beta(board, depth - 1, alpha, beta, 1);
                    board[i][j] = EMPTY;

                    if (eval < min_eval) {
                        min_eval = eval;
                    }
                    if (eval < beta) {
                        beta = eval;
                    }
                    if (beta <= alpha) break;
                }
            }
            if (beta <= alpha) break;
        }

        return min_eval;
    }
}

Move get_best_move(int board[SIZE][SIZE]) {
    Move bestMove;
    bestMove.score = INT_MIN;
    bestMove.x = -1;
    bestMove.y = -1; // null move: (-infinity, -1, -1)

    int alpha = INT_MIN;
    int beta = INT_MAX;

    printf("AI is thinking(depth %d)...\n", SEARCH_DEPTH);

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == EMPTY) {

                board[i][j] = AI;

                int val = minimax_alpha_beta(board, SEARCH_DEPTH - 1, alpha, beta, 0);

                board[i][j] = EMPTY;

                if (val > bestMove.score) {
                    bestMove.score = val;
                    bestMove.x = i;
                    bestMove.y = j;
                }

                if (val > alpha) {
                    alpha = val;
                }
            }
        }
    }
    return bestMove;
}