//
// Created by upsem on 2025/12/8.
//

#include "raylib.h"
#include <math.h>
#define BOARD_SIZE_WITH_SPACE 230

typedef enum {PIECE_BLACK, PIECE_WHITE, PIECE_EMPTY = -1} PieceColor;
const int screenWidth = 1480;
const int screenHeight = 1480;
const int pieceSize = 80;
const double marginWidth = 94.0;
const double cellSideLength = 92.5;
void PositionToCoordinate(Vector2 Position, Vector2 *Coordinate);
void CoordinateToStandardPosition(Vector2 Coordinate, Vector2* Position, Texture2D pieceTexture);

int main() {
    int piecesInPlace[BOARD_SIZE_WITH_SPACE];
    for (int i = 0; i < BOARD_SIZE_WITH_SPACE; i++) {
        piecesInPlace[i] = PIECE_EMPTY;
    }
    Vector2 coordinatesInPlace[BOARD_SIZE_WITH_SPACE] = {};
    for (int i = 0; i < BOARD_SIZE_WITH_SPACE; i++) {
        Vector2 initializer = {0, 0};
        coordinatesInPlace[i] = initializer;
    }
    int pieceCount = 0;

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

    Vector2 piecePosition = {0, 0};
    Vector2 pieceCoordinate = {0, 0};

    int pieceToDraw = PIECE_BLACK;

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


        const char* coordinateIndicator = TextFormat("Position to choose: %d, %d",
            (int)pieceCoordinate.x, (int)pieceCoordinate.y);

        BeginDrawing();
        {
            ClearBackground(RAYWHITE);
            DrawTexture(boardTexture, boardPosX, boardPosY, WHITE);

            // the ghost piece
            Color COVER = Fade(WHITE, 0.6f);
            if (pieceToDraw == PIECE_BLACK) {
                DrawTextureV(whitePieceTexture, drawPos, COVER);
            }
            else {
                DrawTextureV(blackPieceTexture, drawPos, COVER);
            }

            for (int i = 0; i < BOARD_SIZE_WITH_SPACE; i++) {
                DrawTextureV(piecesInPlace[i] ? whitePieceTexture : blackPieceTexture,
                    coordinatesInPlace[i], WHITE);
            }

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                piecesInPlace[pieceCount] = pieceToDraw;
                coordinatesInPlace[pieceCount++] = drawPos;
                isMouseClicked = true;
            }
            if (isMouseClicked) {
                pieceToDraw = !pieceToDraw; // switch piece color
                isMouseClicked = false;
            }

            DrawText(coordinateIndicator, 60, 30, 40, WHITE);
        }
        EndDrawing();
    }

    UnloadTexture(blackPieceTexture);
    UnloadTexture(whitePieceTexture);
    UnloadTexture(boardTexture);
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