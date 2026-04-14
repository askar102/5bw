#include "gameState.h"

void GameState::HandleInput() {
    if (IsKeyPressed(KEY_B)) {
        startBattle = true;
    }
}

void GameState::Draw() {
    ClearBackground(GREEN);
    DrawText("currentState: game(map)", 0, 0, 20, WHITE);
    // todo: delete this in future
    DrawText("NOTE: press B for battle", 0, 30, 20, WHITE);
}

void GameState::Update(float dt) {
    if (startBattle) {
        stateMachine->ChangeState(std::make_unique<BattleState>());
    }
}