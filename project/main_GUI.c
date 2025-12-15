//
// Created by upsem on 2025/12/8.
//

#include "raylib.h"
#include <math.h>
#define BOARD_SIZE_WITH_SPACE 230
#define BOARD_SIZE 15

typedef enum {PIECE_BLACK, PIECE_WHITE, PIECE_EMPTY = -1} PieceColor;
const int screenWidth = 1480;
const int screenHeight = 1480;
const int pieceSize = 80;
const double marginWidth = 94.0;
const double cellSideLength = 92.5;
void PositionToCoordinate(Vector2 Position, Vector2 *Coordinate);
void CoordinateToStandardPosition(Vector2 Coordinate, Vector2* Position, Texture2D pieceTexture);
bool IsIntersectionEmpty(int board[][BOARD_SIZE], int x, int y);
bool isPieceWithinBoundary(int x, int y);

int main() {
    int logicBoard[BOARD_SIZE][BOARD_SIZE];
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            logicBoard[i][j] = PIECE_EMPTY;
        }
    }
    int pieceCount = 0;

    int piecesInPlace[BOARD_SIZE_WITH_SPACE];
    for (int i = 0; i < BOARD_SIZE_WITH_SPACE; i++) {
        piecesInPlace[i] = PIECE_EMPTY;
    }
    Vector2 coordinatesInPlace[BOARD_SIZE_WITH_SPACE] = {};
    for (int i = 0; i < BOARD_SIZE_WITH_SPACE; i++) {
        Vector2 initializer = {0, 0};
        coordinatesInPlace[i] = initializer;
    }


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

    Vector2 piecePosition = {0, 0};
    Vector2 pieceCoordinate = {0, 0};

    int pieceToDraw = PIECE_BLACK;
    Vector2 lastPieceCoordinates = {-2, -2};
    char* superpositionWarning = "";

    SetTargetFPS(120);
    while (!WindowShouldClose()) {

        Vector2 drawPos = {
            piecePosition.x - blackPieceTexture.width / 2.0f,
            piecePosition.y - blackPieceTexture.height / 2.0f
        };

        piecePosition = GetMousePosition();
        PositionToCoordinate(piecePosition, &pieceCoordinate);
        CoordinateToStandardPosition(pieceCoordinate, &drawPos, blackPieceTexture);

        bool isMouseClicked = false;

        const char* coordinateIndicator = TextFormat("(%d, %d)",
            (int)pieceCoordinate.x, (int)pieceCoordinate.y);


        BeginDrawing();
        {
            ClearBackground(RAYWHITE);
            DrawTexture(boardTexture, boardPosX, boardPosY, WHITE);

            // the ghost piece
            Color COVER = Fade(WHITE, 0.6f);
            if (pieceToDraw == PIECE_BLACK) {
                DrawTextureV(blackPieceTexture, drawPos, COVER);
            }
            else {
                DrawTextureV(whitePieceTexture, drawPos, COVER);
            }

            // for (int i = 0; i < BOARD_SIZE_WITH_SPACE; i++) {
            //     if (piecesInPlace[i] == PIECE_EMPTY) break;
            //     DrawTextureV(piecesInPlace[i] ? whitePieceTexture : blackPieceTexture,
            //         coordinatesInPlace[i], WHITE);
            // } // draw pieces on board

            // new drawing pieces
            for (int i = 0; i < BOARD_SIZE; i++) {
                for (int j = 0; j < BOARD_SIZE; j++) {
                    if (logicBoard[i][j] != PIECE_EMPTY) {
                        Vector2 tempCoordinate = {i, j};
                        Vector2 drawPosition = {0.0f, 0.0f};
                        CoordinateToStandardPosition(tempCoordinate, &drawPosition, blackPieceTexture);
                        DrawTextureV(logicBoard[i][j] ? whitePieceTexture : blackPieceTexture,
                            drawPosition, WHITE);
                    }
                }
            }


            // if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            //     if (drawPos.x == coordinatesInPlace[pieceCount - 1].x ||
            //         drawPos.y == coordinatesInPlace[pieceCount - 1].y ) {
            //         superpositionWarning = "You can't place a piece here!";
            //     }
            //     else {
            //         superpositionWarning = "";
            //         piecesInPlace[pieceCount] = pieceToDraw;
            //         coordinatesInPlace[pieceCount++] = drawPos;
            //         isMouseClicked = true;
            //     }
            // }

            // new ver to place and store pieces
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                if (IsIntersectionEmpty(logicBoard, pieceCoordinate.x, pieceCoordinate.y) &&
                    isPieceWithinBoundary((int)pieceCoordinate.x, (int)pieceCoordinate.y)) {
                    logicBoard[(int)pieceCoordinate.x][(int)pieceCoordinate.y] = pieceToDraw;
                    pieceCount++;
                    isMouseClicked = true;
                    superpositionWarning = "";
                    lastPieceCoordinates.x = (int)pieceCoordinate.x;
                    lastPieceCoordinates.y = (int)pieceCoordinate.y;
                    Vector2 tempV = lastPieceCoordinates;
                    CoordinateToStandardPosition(tempV, &lastPieceCoordinates, blackPieceTexture);
                }
                else {
                    superpositionWarning = "You can't place a piece here!";
                }
            }

            // lastPieceCoordinates = coordinatesInPlace[pieceCount - 1];
            // lastPieceCoordinates.x -= highlightTexture.height / 2.0f;
            // lastPieceCoordinates.y -= highlightTexture.width / 2.0f;
            if (lastPieceCoordinates.x > 0) {
                DrawTextureV(highlightTexture, lastPieceCoordinates, WHITE); // highlighting
            }
            if (isMouseClicked) {
                pieceToDraw = !pieceToDraw; // switch piece color
                isMouseClicked = false;
            }

            DrawText(coordinateIndicator, 60, 30, 40, WHITE);
            DrawText(superpositionWarning, 250, 30, 40, WHITE);
        }
        EndDrawing();
    }

    UnloadTexture(blackPieceTexture);
    UnloadTexture(whitePieceTexture);
    UnloadTexture(boardTexture);
    UnloadTexture(highlightTexture);
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

void CoordinateToStandardPosition(Vector2 Coordinate, Vector2* Position, Texture2D pieceTexture) {
    float toPrintX = marginWidth + Coordinate.x * cellSideLength - pieceTexture.width / 2.0f;
    float toPrintY = marginWidth + Coordinate.y * cellSideLength - pieceTexture.width / 2.0f;
    Position->x = toPrintX;
    Position->y = toPrintY;
}

bool IsIntersectionEmpty(int board[][BOARD_SIZE], int x, int y) {
    if (board[x][y] == PIECE_EMPTY) return true;
    return false;
}

bool isPieceWithinBoundary(int x, int y) {
    if (x < 15 && x >= 0 && y < 15 && y >= 0) return true;
    return false;
}