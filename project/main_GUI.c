//
// Created by upsem on 2025/12/8.
//
#include <math.h>
#include "search.h"
#include "evaluate.h"
#include "GUI.h"


int main() {
    int logicBoard[BOARD_SIZE][BOARD_SIZE];
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            logicBoard[i][j] = PIECE_EMPTY;
        }
    }
    int pieceCount = 0;
    GameState currentState = STATE_PLAYER_TURN;

    InitWindow(screenWidth, screenHeight, "test1");

    // load board
    Image board = LoadImage("assets/board_HD.jpg");
    ImageResize(&board, screenWidth, screenHeight);
    Texture2D boardTexture = LoadTextureFromImage(board);
    const int boardPosX = (screenHeight - boardTexture.height) / 2;
    const int boardPosY = (screenWidth - boardTexture.width) / 2;
    UnloadImage(board);

    // load black piece
    Image blackPiece = LoadImage("assets/stone_black.png");
    ImageResize(&blackPiece,  pieceSize,pieceSize);
    Texture2D blackPieceTexture = LoadTextureFromImage(blackPiece);
    UnloadImage(blackPiece);

    // load white piece
    Image whitePiece = LoadImage("assets/stone_white.png");
    ImageResize(&whitePiece, pieceSize, pieceSize);
    Texture2D whitePieceTexture = LoadTextureFromImage(whitePiece);
    UnloadImage(whitePiece);

    // load highlight indicator
    Image highlight = LoadImage("assets/stone_highlight_glow.png");
    ImageResize(&highlight, pieceSize, pieceSize);
    Texture2D highlightTexture = LoadTextureFromImage(highlight);
    UnloadImage(highlight);

    // load font
    Font notoSerifSC = LoadFont("assets/NotoSerifSC-Bold.ttf");
    Font quickSand = LoadFont("assets/Quicksand-Bold.ttf");

    Vector2 piecePosition = {0, 0};
    Vector2 ghostPieceCoordinate = {0, 0};

    int pieceToDrawColor = PIECE_BLACK;
    Vector2 lastPieceCoordinates = {-2, -2};
    char* superpositionWarning = "";

    SetTargetFPS(120);
    while (!WindowShouldClose()) {

        Vector2 drawPos = {
            piecePosition.x - blackPieceTexture.width / 2.0f,
            piecePosition.y - blackPieceTexture.height / 2.0f
        };

        piecePosition = GetMousePosition();
        PositionToCoordinate(piecePosition, &ghostPieceCoordinate);
        CoordinateToPosition(ghostPieceCoordinate, &drawPos, blackPieceTexture);


        const char* coordinateIndicator = TextFormat("(%d, %d)",
            (int)ghostPieceCoordinate.x, (int)ghostPieceCoordinate.y);


        BeginDrawing();
        {
            ClearBackground(RAYWHITE);
            DrawTexture(boardTexture, boardPosX, boardPosY, WHITE);

            // the ghost piece
            Color COVER = Fade(WHITE, 0.6f);
            if (pieceToDrawColor == PIECE_BLACK) {
                DrawTextureV(blackPieceTexture, drawPos, COVER);
            }
            else {
                DrawTextureV(whitePieceTexture, drawPos, COVER);
            }

            // drawing pieces on board
            for (int row = 0; row < BOARD_SIZE; row++) {
                for (int col = 0; col < BOARD_SIZE; col++) {
                    if (logicBoard[row][col] != PIECE_EMPTY) {
                        Vector2 tempCoordinate = {col, row};
                        Vector2 drawPosition = {0.0f, 0.0f};
                        CoordinateToPosition(tempCoordinate, &drawPosition, blackPieceTexture);
                        DrawTextureV(logicBoard[row][col] ? whitePieceTexture : blackPieceTexture,
                            drawPosition, WHITE);
                    }
                }
            }


            // place and store pieces
            if (!is_game_over(logicBoard)) {
                if (currentState == STATE_PLAYER_TURN) {
                    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                        if (IsIntersectionEmpty(logicBoard, ghostPieceCoordinate.x, ghostPieceCoordinate.y) &&
                            isPieceWithinBoundary((int)ghostPieceCoordinate.x, (int)ghostPieceCoordinate.y)) {
                            logicBoard[(int)ghostPieceCoordinate.y][(int)ghostPieceCoordinate.x] = pieceToDrawColor;
                            pieceCount++;
                            superpositionWarning = "";
                            lastPieceCoordinates.x = (int)ghostPieceCoordinate.x;
                            lastPieceCoordinates.y = (int)ghostPieceCoordinate.y;
                            Vector2 tempV = lastPieceCoordinates;
                            CoordinateToPosition(tempV, &lastPieceCoordinates, blackPieceTexture);
                            currentState = STATE_AI_TURN;
                            pieceToDrawColor = !pieceToDrawColor;
                            }
                        else {
                            superpositionWarning = "You can't place a piece here!";
                        }
                    }
                }
                else if (currentState == STATE_AI_TURN){ // AI's turn
                    BeginDrawing();
                    Vector2 supWarCoo = {442, 30};
                    DrawTextEx(quickSand, "Thinking...", supWarCoo, 60, 0, WHITE);
                    EndDrawing();
                    Move bestMove = get_best_move(logicBoard);
                    logicBoard[bestMove.x][bestMove.y] = pieceToDrawColor;
                    pieceCount++;
                    superpositionWarning = "";
                    lastPieceCoordinates.x = bestMove.y;
                    lastPieceCoordinates.y = bestMove.x;
                    Vector2 tempV = lastPieceCoordinates;
                    CoordinateToPosition(tempV, &lastPieceCoordinates, blackPieceTexture);
                    currentState = STATE_PLAYER_TURN;
                    pieceToDrawColor = !pieceToDrawColor;
                }
            }
            else {
                Vector2 supWarCoo = {screenWidth / 2.0f, screenHeight / 2.0f};
                if (pieceCount != MAX_PIECE_COUNT) {
                    if (currentState == STATE_AI_TURN) {
                        DrawTextEx(quickSand, "Player Wins!", supWarCoo, 150, 0, WHITE);
                    }
                    if (currentState == STATE_PLAYER_TURN) {
                        DrawTextEx(quickSand, "AI wins!", supWarCoo, 150, 0, WHITE);
                    }
                }
                else {
                    Vector2 supWarCoo = {442, 30};
                    DrawTextEx(quickSand, "Draw!", supWarCoo, 60, 0, WHITE);
                }
            }

            if (lastPieceCoordinates.x > 0) {
                DrawTextureV(highlightTexture, lastPieceCoordinates, WHITE); // highlighting
            }


            // DrawText(coordinateIndicator, 60, 30, 40, WHITE);
            Vector2 cooIndCoo = {60, 30};
            DrawTextEx(quickSand, coordinateIndicator, cooIndCoo, 60, 0, WHITE);
            // DrawText(superpositionWarning, 442, 30, 40, WHITE);
            Vector2 supWarCoo = {442, 30};
            DrawTextEx(quickSand, superpositionWarning, supWarCoo, 60, 0, WHITE);
        }
        EndDrawing();
    }

    UnloadTexture(blackPieceTexture);
    UnloadTexture(whitePieceTexture);
    UnloadTexture(boardTexture);
    UnloadTexture(highlightTexture);
    UnloadFont(notoSerifSC);
    UnloadFont(quickSand);

    CloseWindow();

    return 0;
}

void PositionToCoordinate(Vector2 Position, Vector2 *Coordinate) {
    float inBoardX = Position.x - marginWidth;
    float inBoardY = Position.y - marginWidth;
    int col = (int)roundf(inBoardX / cellSideLength);
    int row = (int)roundf(inBoardY / cellSideLength);
    Coordinate->x = col;
    Coordinate->y = row;
}

void CoordinateToPosition(Vector2 Coordinate, Vector2* Position, Texture2D pieceTexture) {
    float toPrintX = marginWidth + Coordinate.x * cellSideLength - pieceTexture.width / 2.0f;
    float toPrintY = marginWidth + Coordinate.y * cellSideLength - pieceTexture.width / 2.0f;
    Position->x = toPrintX;
    Position->y = toPrintY;
}

bool IsIntersectionEmpty(int board[][BOARD_SIZE], int x, int y) {
    if (board[y][x] == PIECE_EMPTY) return true;
    return false;
}

bool isPieceWithinBoundary(int x, int y) {
    if (x < 15 && x >= 0 && y < 15 && y >= 0) return true;
    return false;
}