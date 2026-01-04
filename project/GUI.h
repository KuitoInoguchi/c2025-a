//
// Created by upsem on 2025/12/28.
//

#ifndef C2025_CHALLENGE_GUI_H
#define C2025_CHALLENGE_GUI_H
#include "raylib.h"
#define BOARD_SIZE_WITH_SPACE 230
#define BOARD_SIZE 15
#define MAX_PIECE_COUNT 255
typedef enum {PIECE_BLACK, PIECE_WHITE, PIECE_EMPTY = -1} PieceColor;
typedef enum {STATE_PLAYER_TURN, STATE_AI_TURN, STATE_GAME_OVER} GameState;
const int screenWidth = 1480;
const int screenHeight = 1480;
const int pieceSize = 80;
const double marginWidth = 94.0;
const double cellSideLength = 92.5;
void PositionToCoordinate(Vector2 Position, Vector2 *Coordinate);
void CoordinateToPosition(Vector2 Coordinate, Vector2* Position, Texture2D pieceTexture);
bool IsIntersectionEmpty(int board[][BOARD_SIZE], int x, int y);
bool isPieceWithinBoundary(int x, int y);
#endif //C2025_CHALLENGE_GUI_H