#include "battleState.h"

void BattleState::HandleInput() {
    // if (IsKeyPressed(KEY_B)) {
    //     startBattle = true;
    // }
}

void BattleState::Draw() {
    ClearBackground(RED);
    DrawText("currentState: battle", 0, 0, 20, WHITE);
    // todo: delete this in future
    DrawText("NOTE: fcku, is last state", 0, 30, 20, WHITE);
}

void BattleState::Update(float dt) {
    // if (startBattle) {
    //     // stateMachine->ChangeState(std::make_unique<GameState>());
    // }
}