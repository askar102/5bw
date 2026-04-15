#include "mapState.h"

void MapState::HandleInput() {
    if (IsKeyPressed(KEY_B)) {
        startBattle = true;
    }
}

void MapState::Draw() {
    ClearBackground(GREEN);
    DrawText("currentState: game(map)", 0, 0, 20, WHITE);
    // todo: delete this in future
    DrawText("NOTE: press B for battle", 0, 30, 20, WHITE);
}

void MapState::Update(float dt) {
    if (startBattle && stateMachine) {
        startBattle = false;
        stateMachine->ChangeState(std::make_unique<BattleState>());
    }
}