#include "game.h"
#include "../raylib/raylib.h"
#include "../states/menuState.h"

Game::Game(int width, int height, const char* title)
    : screenWidth(width),
      screenHeight(height),
      windowTitle(title),
      running(true) {}

Game::~Game() {
    Shutdown();
}

void Game::Init() {
    InitWindow(screenWidth, screenHeight, windowTitle);
    SetTargetFPS(60);

    stateMachine.ChangeState(std::make_unique<MenuState>());
}

void Game::Run() {
    Init();

    while (!WindowShouldClose() && running) {
        Update();
        Draw();
    }

    Shutdown();
}

void Game::Update() {
    float dt = GetFrameTime();

    stateMachine.HandleInput();
    stateMachine.Update(dt);
}

void Game::Draw() {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    stateMachine.Draw();

    EndDrawing();
}

void Game::Shutdown() {
    CloseWindow();
}

void Game::ChangeState(std::unique_ptr<State> newState) {
    stateMachine.ChangeState(std::move(newState));
}