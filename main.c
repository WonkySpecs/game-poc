#include "raylib.h"
#include <stdio.h>

#include "player.h"
#include "constants.h"

static void UpdateFrame(float delta);
static void DrawFrame(void);

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Twin Stick Slasker PoC");
    InitPlayer();

    SetTargetFPS(60);

    // Main game loop
    while (!WindowShouldClose())
    {
        UpdateFrame(GetFrameTime() / TARGET_FRAME_TIME);
        DrawFrame();
    }

    UnloadPlayer();
    CloseWindow();        // Close window and OpenGL context
    return 0;
}

static void UpdateFrame(float delta) {
    UpdatePlayer(delta);
}

static void DrawFrame() {
        BeginDrawing();

            ClearBackground(RAYWHITE);
            DrawPlayer();

        EndDrawing();
}
