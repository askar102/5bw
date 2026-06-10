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
  Game game(1280, 720, "5bw1.2.2");
  game.Run();

  return 0;
}
