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

  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  Game game(640, 480, "5bw1.2.2");
  game.Run();

  return 0;
}
