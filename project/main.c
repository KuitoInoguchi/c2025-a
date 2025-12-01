//
// Created by upsem on 2025/11/10.
//
#include <stdio.h>
#include <stdlib.h>

#include "general_header.h"
#include "evaluate.h"

void print_board(int board[SIZE][SIZE]) {
    printf("\n   ");
    for (int i = 0; i < SIZE; i++) {
        printf("%2d ", i); // 打印列号
    }
    printf("\n");

    for (int i = 0; i < SIZE; i++) {
        printf("%2d ", i); // 打印行号
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == EMPTY) printf(" . ");
            else if (board[i][j] == AI) printf(" X "); // AI 是 X
            else if (board[i][j] == PLAYER) printf(" O "); // 你是 O
        }
        printf("\n");
    }
    printf("\n");
}

// --- Main Game Loop (English) ---
int main() {
    int board[SIZE][SIZE] = {0};

    int turn = PLAYER; // Human goes first
    int game_running = 1;

    printf("=== Gomoku AI Test Version ===\n");
    printf("Board Size: %dx%d\n", SIZE, SIZE);
    printf("Player (O) vs AI (X)\n");

    print_board(board);

    while (game_running) {

        if (turn == PLAYER) {
            // --- Player Turn ---
            int r, c;
            printf("Your turn (Enter Row Col, e.g., 7 7): ");

            if (scanf("%d %d", &r, &c) != 2) {
                printf("Invalid input format!\n");
                while(getchar() != '\n'); // Clear buffer
                continue;
            }

            // Check validity
            if (r < 0 || r >= SIZE || c < 0 || c >= SIZE || board[r][c] != EMPTY) {
                printf("Invalid move or cell occupied, please try again!\n");
                continue;
            }

            board[r][c] = PLAYER;
        }
        else {
            // --- AI Turn ---
            Move ai_move = get_best_move(board);

            if (ai_move.x == -1) {
                printf("Draw! (No moves left for AI)\n");
                break;
            }

            board[ai_move.x][ai_move.y] = AI;
            printf("AI move: %d %d (Score: %d)\n", ai_move.x, ai_move.y, ai_move.score);
        }

        print_board(board);

        // Check Winner
        if (is_game_over(board)) {
            if (turn == PLAYER) printf("Congratulations! You won!\n");
            else printf("Sorry, AI won!\n");
            game_running = 0;
        }

        // Switch Turn
        turn = (turn == PLAYER) ? AI : PLAYER;
    }

    system("pause"); // Keep window open
    return 0;
}