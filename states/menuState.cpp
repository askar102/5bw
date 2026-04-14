#include "menuState.h"

void MenuState::HandleInput() {
    if (IsKeyPressed(KEY_ENTER)) {
        startPressed = true;
    }
}

void MenuState::Draw() {
    ClearBackground(BLUE);
    DrawText("MENU, PRESS ENTER", 400, 300, 20, WHITE);
}

void MenuState::Update(float dt) {
    if (startPressed) {
        // stateMachine->ChangeState(std::make_unique<GameState>());
    }
}