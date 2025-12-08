#include "raylib.h"
#include <stdio.h>
#include <math.h>
#include "evaluate.h"
#include "general_header.h"

// --- 界面配置 ---
#define WINDOW_WIDTH 900
#define WINDOW_HEIGHT 900

// 这里的参数要根据你的 Python 脚本生成的逻辑来调整
// 假设棋盘边缘留白是总宽度的 1/16
// 我们可以通过数学计算反推格子大小
const float BOARD_MARGIN_RATIO = 1.0f / 16.0f; 

// 引用 AI 函数
extern Move get_best_move(int board[SIZE][SIZE]);

int main(void) {
    // 1. 初始化窗口
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Gomoku - Professional Edition");
    SetTargetFPS(60);

    // 2. 加载高清素材 (确保这些文件在 exe 旁边)
    Texture2D texBoard = LoadTexture("board_HD.jpg");
    Texture2D texBlack = LoadTexture("stone_black.png");
    Texture2D texWhite = LoadTexture("stone_white.png");
    Texture2D texShadow = LoadTexture("stone_shadow.png");
    
    // 如果加载失败，给个提示
    if (texBoard.id == 0) printf("Error: board_HD.jpg not found!\n");

    // 3. 计算布局 (核心数学部分)
    // 我们把棋盘图缩放到窗口大小 (留一点边距)
    float boardScreenSize = WINDOW_HEIGHT * 0.95f; // 棋盘占屏幕高度的 95%
    float boardOffsetX = (WINDOW_WIDTH - boardScreenSize) / 2.0f; // 居中
    float boardOffsetY = (WINDOW_HEIGHT - boardScreenSize) / 2.0f; // 居中

    // 计算每个格子的间距
    // 这里的数学逻辑：棋盘总宽 - 左右两边的留白，剩下的距离除以 (15-1) 个间隔
    float marginSize = boardScreenSize * BOARD_MARGIN_RATIO;
    float playableWidth = boardScreenSize - (2 * marginSize);
    float cellSize = playableWidth / (SIZE - 1);
    
    // 棋子的大小通常是格子大小的 90% 到 95%
    float stoneScale = (cellSize * 0.95f) / texBlack.width; 

    // 4. 游戏数据
    int board[SIZE][SIZE] = {0};
    int turn = PLAYER; 
    int gameOver = 0;
    int winner = 0;

    // --- 主循环 ---
    while (!WindowShouldClose()) {
        
        // --- 逻辑计算 ---
        int hoverRow = -1;
        int hoverCol = -1;

        // 计算鼠标所在的格子
        if (!gameOver) {
            Vector2 mousePos = GetMousePosition();
            
            // 暴力遍历所有交叉点，找鼠标离谁最近
            // (这是最笨但最不容易出错的方法)
            float minDistance = cellSize / 2.0f; // 只有在格子半径内才算
            
            for (int r = 0; r < SIZE; r++) {
                for (int c = 0; c < SIZE; c++) {
                    float cx = boardOffsetX + marginSize + c * cellSize;
                    float cy = boardOffsetY + marginSize + r * cellSize;
                    
                    float dist = sqrtf(powf(mousePos.x - cx, 2) + powf(mousePos.y - cy, 2));
                    
                    if (dist < minDistance) {
                        hoverRow = r;
                        hoverCol = c;
                    }
                }
            }

            // 玩家落子
            if (turn == PLAYER && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                if (hoverRow != -1 && board[hoverRow][hoverCol] == EMPTY) {
                    board[hoverRow][hoverCol] = PLAYER;
                    if (is_game_over(board)) { gameOver = 1; winner = PLAYER; }
                    else turn = AI;
                }
            }
            // AI 落子 (为了防止卡顿，这里应该把计算分帧，但简单起见先这样)
            else if (turn == AI) {
                // 强制渲染一帧"思考中"
                BeginDrawing();
                    // ... (这里可以简略重画背景)
                    DrawText("AI Thinking...", 20, 20, 30, DARKBLUE);
                EndDrawing();

                Move move = get_best_move(board);
                if (move.x != -1) {
                    board[move.x][move.y] = AI;
                    if (is_game_over(board)) { gameOver = 1; winner = AI; }
                    else turn = PLAYER;
                }
            }
        }

        // --- 渲染绘制 (Layers) ---
        BeginDrawing();
        ClearBackground((Color){30, 30, 30, 255}); // 深灰色背景衬托木纹

        // Layer 1: 棋盘背景
        // 使用 DrawTexturePro 进行缩放绘制
        Rectangle srcRect = {0, 0, texBoard.width, texBoard.height};
        Rectangle destRect = {boardOffsetX, boardOffsetY, boardScreenSize, boardScreenSize};
        DrawTexturePro(texBoard, srcRect, destRect, (Vector2){0,0}, 0.0f, WHITE);

        // Layer 2 & 3: 棋子 (阴影 + 本体)
        for (int r = 0; r < SIZE; r++) {
            for (int c = 0; c < SIZE; c++) {
                if (board[r][c] != EMPTY) {
                    // 计算屏幕坐标
                    float cx = boardOffsetX + marginSize + c * cellSize;
                    float cy = boardOffsetY + marginSize + r * cellSize;
                    
                    // 目标绘制位置 (居中)
                    // 纹理中心点需要对齐 cx, cy
                    float drawX = cx - (texBlack.width * stoneScale) / 2;
                    float drawY = cy - (texBlack.height * stoneScale) / 2;

                    // A. 画阴影 (偏移 5像素)
                    // 使用 Fade(WHITE, 0.5f) 让阴影半透明
                    DrawTextureEx(texShadow, (Vector2){drawX + 6, drawY + 6}, 0.0f, stoneScale, Fade(BLACK, 0.4f));

                    // B. 画棋子
                    if (board[r][c] == PLAYER)
                        DrawTextureEx(texBlack, (Vector2){drawX, drawY}, 0.0f, stoneScale, WHITE);
                    else 
                        DrawTextureEx(texWhite, (Vector2){drawX, drawY}, 0.0f, stoneScale, WHITE);
                }
            }
        }

        // Layer 4: 幽灵棋子 (Ghost Stone) - 交互反馈
        // 只有轮到玩家，且鼠标指着空位时才显示
        if (!gameOver && turn == PLAYER && hoverRow != -1 && board[hoverRow][hoverCol] == EMPTY) {
            float cx = boardOffsetX + marginSize + hoverCol * cellSize;
            float cy = boardOffsetY + marginSize + hoverRow * cellSize;
            float drawX = cx - (texBlack.width * stoneScale) / 2;
            float drawY = cy - (texBlack.height * stoneScale) / 2;
            
            // 画一个半透明的黑色棋子，表示"如果你点这里，会落黑子"
            // Fade(WHITE, 0.6f) 意思是 60% 不透明度
            DrawTextureEx(texBlack, (Vector2){drawX, drawY}, 0.0f, stoneScale, Fade(WHITE, 0.6f));
        }
        
        // Layer 5: 胜利结算 UI
        if (gameOver) {
            const char* text = (winner == PLAYER) ? "YOU WIN!" : "AI WINS!";
            int textWidth = MeasureText(text, 60);
            
            // 画一个半透明黑框做背景
            DrawRectangle(0, WINDOW_HEIGHT/2 - 50, WINDOW_WIDTH, 100, Fade(BLACK, 0.7f));
            DrawText(text, (WINDOW_WIDTH - textWidth)/2, WINDOW_HEIGHT/2 - 30, 60, GOLD);
            DrawText("Press SPACE to Restart", (WINDOW_WIDTH - MeasureText("Press SPACE to Restart", 20))/2, WINDOW_HEIGHT/2 + 40, 20, LIGHTGRAY);
            
            if (IsKeyPressed(KEY_SPACE)) {
                // 重置游戏
                for(int i=0; i<SIZE; i++) for(int j=0; j<SIZE; j++) board[i][j] = EMPTY;
                turn = PLAYER;
                gameOver = 0;
            }
        }

        EndDrawing();
    }

    // 卸载素材
    UnloadTexture(texBoard);
    UnloadTexture(texBlack);
    UnloadTexture(texWhite);
    UnloadTexture(texShadow);

    CloseWindow();
    return 0;
}