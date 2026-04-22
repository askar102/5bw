#include "battleState.h"

void BattleState::HandleInput() {
    // if (IsKeyPressed(KEY_B)) {
    //     startBattle = true;
    // }
}

void BattleState::Draw() {
    ClearBackground(RED);

    _background.Draw();

    DrawText("currentState: battle", 0, 0, 20, WHITE);
    // todo: delete this in future
    DrawText("NOTE: fcku, is last state", 0, 30, 20, WHITE);
}

void BattleState::Update(float dt) {
    // if (startBattle) {
    //     // stateMachine->ChangeState(std::make_unique<GameState>());
    // }
}

void BattleState::OnEnter() {
    this->LoadResources();

    // start logic
    _background.setSize(800, 600);
}

void BattleState::OnExit() {
    this->UnloadResources();
}

void BattleState::LoadResources() {
    _backgroundTexture = LoadTexture("resources/battle.png");
    _background.setTexture(&_backgroundTexture);
}

void BattleState::UnloadResources() {
    UnloadTexture(_backgroundTexture);
}