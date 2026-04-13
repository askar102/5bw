#include "raylib/raylib.h"

int main() {
    InitWindow(800, 450, "5bw12");

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // тут рисование

        EndDrawing();
    }

    CloseWindow();
    return 0;
}