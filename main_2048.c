#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GRID_SIZE 4
#define TILE_SIZE 100
#define TILE_GAP 10
#define GRID_OFFSET_X 180
#define GRID_OFFSET_Y 100
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define FPS 60

static struct {
    int grid[GRID_SIZE][GRID_SIZE];
    int score;
    bool gameOver;
    bool win;
} s_2048State;

static void GenerateNewTile(void);
static bool CanMove(void);
static bool MoveLeft(void);
static bool MoveRight(void);
static bool MoveUp(void);
static bool MoveDown(void);
static Color GetTileColor(int value);
static void Game2048_Init(void);
static void Game2048_Update(void);
static void Game2048_Draw(void);

static void GenerateNewTile(void) {
    int emptyTiles[GRID_SIZE * GRID_SIZE][2];
    int emptyCount = 0;

    for (int y = 0; y < GRID_SIZE; y++) {
        for (int x = 0; x < GRID_SIZE; x++) {
            if (s_2048State.grid[y][x] == 0) {
                emptyTiles[emptyCount][0] = x;
                emptyTiles[emptyCount][1] = y;
                emptyCount++;
            }
        }
    }

    if (emptyCount > 0) {
        int index = rand() % emptyCount;
        int x = emptyTiles[index][0];
        int y = emptyTiles[index][1];
        s_2048State.grid[y][x] = (rand() % 10 < 9) ? 2 : 4;
    }
}

static bool CanMove(void) {
    for (int y = 0; y < GRID_SIZE; y++) {
        for (int x = 0; x < GRID_SIZE; x++) {
            if (s_2048State.grid[y][x] == 0) return true;
        }
    }

    for (int y = 0; y < GRID_SIZE; y++) {
        for (int x = 0; x < GRID_SIZE; x++) {
            int current = s_2048State.grid[y][x];
            if (x < GRID_SIZE - 1 && current == s_2048State.grid[y][x+1]) return true;
            if (y < GRID_SIZE - 1 && current == s_2048State.grid[y+1][x]) return true;
        }
    }
    return false;
}

static bool MoveLeft(void) {
    bool moved = false;
    for (int y = 0; y < GRID_SIZE; y++) {
        int temp[GRID_SIZE] = {0};
        int index = 0;
        for (int x = 0; x < GRID_SIZE; x++) {
            if (s_2048State.grid[y][x] != 0) {
                temp[index++] = s_2048State.grid[y][x];
            }
        }

        for (int i = 0; i < GRID_SIZE - 1; i++) {
            if (temp[i] != 0 && temp[i] == temp[i+1]) {
                temp[i] *= 2;
                s_2048State.score += temp[i];
                temp[i+1] = 0;
                moved = true;
            }
        }

        int final[GRID_SIZE] = {0};
        index = 0;
        for (int i = 0; i < GRID_SIZE; i++) {
            if (temp[i] != 0) {
                final[index++] = temp[i];
            }
        }

        for (int x = 0; x < GRID_SIZE; x++) {
            if (s_2048State.grid[y][x] != final[x]) {
                moved = true;
                s_2048State.grid[y][x] = final[x];
            }
        }
    }
    return moved;
}

static bool MoveRight(void) {
    bool moved = false;
    for (int y = 0; y < GRID_SIZE; y++) {
        int temp[GRID_SIZE] = {0};
        int index = GRID_SIZE - 1;
        for (int x = GRID_SIZE - 1; x >= 0; x--) {
            if (s_2048State.grid[y][x] != 0) {
                temp[index--] = s_2048State.grid[y][x];
            }
        }

        for (int i = GRID_SIZE - 1; i > 0; i--) {
            if (temp[i] != 0 && temp[i] == temp[i-1]) {
                temp[i] *= 2;
                s_2048State.score += temp[i];
                temp[i-1] = 0;
                moved = true;
            }
        }

        int final[GRID_SIZE] = {0};
        index = GRID_SIZE - 1;
        for (int i = GRID_SIZE - 1; i >= 0; i--) {
            if (temp[i] != 0) {
                final[index--] = temp[i];
            }
        }

        for (int x = 0; x < GRID_SIZE; x++) {
            if (s_2048State.grid[y][x] != final[x]) {
                moved = true;
                s_2048State.grid[y][x] = final[x];
            }
        }
    }
    return moved;
}

static bool MoveUp(void) {
    bool moved = false;
    for (int x = 0; x < GRID_SIZE; x++) {
        int temp[GRID_SIZE] = {0};
        int index = 0;
        for (int y = 0; y < GRID_SIZE; y++) {
            if (s_2048State.grid[y][x] != 0) {
                temp[index++] = s_2048State.grid[y][x];
            }
        }

        for (int i = 0; i < GRID_SIZE - 1; i++) {
            if (temp[i] != 0 && temp[i] == temp[i+1]) {
                temp[i] *= 2;
                s_2048State.score += temp[i];
                temp[i+1] = 0;
                moved = true;
            }
        }

        int final[GRID_SIZE] = {0};
        index = 0;
        for (int i = 0; i < GRID_SIZE; i++) {
            if (temp[i] != 0) {
                final[index++] = temp[i];
            }
        }

        for (int y = 0; y < GRID_SIZE; y++) {
            if (s_2048State.grid[y][x] != final[y]) {
                moved = true;
                s_2048State.grid[y][x] = final[y];
            }
        }
    }
    return moved;
}

static bool MoveDown(void) {
    bool moved = false;
    for (int x = 0; x < GRID_SIZE; x++) {
        int temp[GRID_SIZE] = {0};
        int index = GRID_SIZE - 1;
        for (int y = GRID_SIZE - 1; y >= 0; y--) {
            if (s_2048State.grid[y][x] != 0) {
                temp[index--] = s_2048State.grid[y][x];
            }
        }

        for (int i = GRID_SIZE - 1; i > 0; i--) {
            if (temp[i] != 0 && temp[i] == temp[i-1]) {
                temp[i] *= 2;
                s_2048State.score += temp[i];
                temp[i-1] = 0;
                moved = true;
            }
        }

        int final[GRID_SIZE] = {0};
        index = GRID_SIZE - 1;
        for (int i = GRID_SIZE - 1; i >= 0; i--) {
            if (temp[i] != 0) {
                final[index--] = temp[i];
            }
        }

        for (int y = 0; y < GRID_SIZE; y++) {
            if (s_2048State.grid[y][x] != final[y]) {
                moved = true;
                s_2048State.grid[y][x] = final[y];
            }
        }
    }
    return moved;
}

static Color GetTileColor(int value) {
    switch (value) {
        case 2:    return (Color){238, 228, 218, 255};
        case 4:    return (Color){237, 224, 200, 255};
        case 8:    return (Color){242, 177, 121, 255};
        case 16:   return (Color){245, 149, 99, 255};
        case 32:   return (Color){246, 124, 95, 255};
        case 64:   return (Color){246, 94, 59, 255};
        case 128:  return (Color){237, 207, 114, 255};
        case 256:  return (Color){237, 204, 97, 255};
        case 512:  return (Color){237, 200, 80, 255};
        case 1024: return (Color){237, 197, 63, 255};
        case 2048: return (Color){237, 194, 46, 255};
        default:   return (Color){205, 193, 180, 255};
    }
}

static void Game2048_Init(void) {
    memset(&s_2048State, 0, sizeof(s_2048State));
    GenerateNewTile();
    GenerateNewTile();
}

static void Game2048_Update(void) {
    if (s_2048State.gameOver || s_2048State.win) {
        if (IsKeyPressed(KEY_R)) {
            Game2048_Init();
        }
        return;
    }

    bool moved = false;
    if (IsKeyPressed(KEY_LEFT))  moved = MoveLeft();
    if (IsKeyPressed(KEY_RIGHT)) moved = MoveRight();
    if (IsKeyPressed(KEY_UP))    moved = MoveUp();
    if (IsKeyPressed(KEY_DOWN))  moved = MoveDown();

    if (moved) {
        GenerateNewTile();
        for (int y = 0; y < GRID_SIZE; y++) {
            for (int x = 0; x < GRID_SIZE; x++) {
                if (s_2048State.grid[y][x] == 2048) {
                    s_2048State.win = true;
                }
            }
        }
        if (!CanMove()) {
            s_2048State.gameOver = true;
        }
    }
}

static void Game2048_Draw(void) {
    ClearBackground((Color){250, 248, 239, 255});
    DrawText("2048", 320, 30, 48, (Color){119, 110, 101, 255});
    
    char scoreText[32];
    sprintf(scoreText, "score: %d", s_2048State.score);
    DrawText(scoreText, GRID_OFFSET_X, GRID_OFFSET_Y - 50, 24, (Color){119, 110, 101, 255});
    DrawText("R Restart", GRID_OFFSET_X, 550, 20, GRAY);

    DrawRectangle(GRID_OFFSET_X - TILE_GAP, GRID_OFFSET_Y - TILE_GAP,
                  GRID_SIZE * (TILE_SIZE + TILE_GAP) + TILE_GAP,
                  GRID_SIZE * (TILE_SIZE + TILE_GAP) + TILE_GAP,
                  (Color){187, 173, 160, 255});

    for (int y = 0; y < GRID_SIZE; y++) {
        for (int x = 0; x < GRID_SIZE; x++) {
            int value = s_2048State.grid[y][x];
            int posX = GRID_OFFSET_X + x * (TILE_SIZE + TILE_GAP);
            int posY = GRID_OFFSET_Y + y * (TILE_SIZE + TILE_GAP);

            DrawRectangle(posX, posY, TILE_SIZE, TILE_SIZE, GetTileColor(value));

            if (value != 0) {
                char text[8];
                sprintf(text, "%d", value);
                int fontSize = (value < 100) ? 36 : (value < 1000) ? 32 : 24;
                int textWidth = MeasureText(text, fontSize);
                Color textColor = (value <= 4) ? (Color){119, 110, 101, 255} : WHITE;
                DrawText(text, posX + (TILE_SIZE - textWidth)/2, posY + (TILE_SIZE - fontSize)/2, fontSize, textColor);
            }
        }
    }

    if (s_2048State.win || s_2048State.gameOver) {
        DrawRectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, (Color){0, 0, 0, 180});
        const char* text = s_2048State.win ? "You Win!" : "Game Over!";
        int textWidth = MeasureText(text, 60);
        DrawText(text, (WINDOW_WIDTH - textWidth)/2, 220, 60, WHITE);
        DrawText("Press R to Restart", 280, 320, 30, WHITE);
    }
}

int main(void) {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "2048 Game");
    SetTargetFPS(FPS);
    
    Game2048_Init();
    
    while (!WindowShouldClose()) {
        Game2048_Update();
        
        BeginDrawing();
        Game2048_Draw();
        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}