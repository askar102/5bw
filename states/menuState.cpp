#include "menuState.h"
#include "gameState.h"

void MenuState::HandleInput() {
    if (IsKeyPressed(KEY_ENTER)) {
        startPressed = true;
    }
}

void MenuState::Draw() {
    ClearBackground(BLUE);
    DrawText("currentState: menu", 0, 0, 20, WHITE);
    // todo: delete this in future
    DrawText("NOTE: press Enter", 0, 30, 20, WHITE);
}

void MenuState::Update(float dt) {
    if (startPressed) {
        stateMachine->ChangeState(std::make_unique<GameState>());
    }
}