// #include "raylib/raylib.h"

// int main() {
//     InitWindow(800, 450, "5bw12");

//     SetTargetFPS(60);

//     while (!WindowShouldClose()) {
//         BeginDrawing();
//         ClearBackground(RAYWHITE);

//         // тут рисование

//         EndDrawing();
//     }

//     CloseWindow();
//     return 0;
// }


#include "core/game.h"

int main() {
    Game game(800, 600, "5bw12");
    game.Run();
    return 0;
}