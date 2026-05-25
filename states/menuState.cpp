/**
 * @file menuState.cpp
 * @author askar102
 * @brief Menu scene
 * @date 2026-05-07
 * 
 * @copyright Copyright (c) 2026, askar102
 * 
 */

#include "menuState.h"

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

    _startButton.Draw();
}

void MenuState::Update(float dt) {
    if (startPressed) {
        stateMachine->ChangeState(std::make_unique<MapState>());
    }

    _startButton.Update();
}
void MenuState::OnEnter() {
    _startButton.SetLabel("Start");
    _startButton.SetPosition({400, 300});
    _startButton.SetOnClick([this]() {
        stateMachine->ChangeState(std::make_unique<MapState>());
    }); 
}