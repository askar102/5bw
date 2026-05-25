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

    _gui.Draw(); 
}

void MenuState::Update(float dt) {
    if (startPressed) {
        stateMachine->ChangeState(std::make_unique<MapState>());
    }

    _gui.Update();
}
void MenuState::OnEnter() {
    InitGui();
}

void MenuState::OnExit() {
    _gui.Clear();
}

void MenuState::InitGui() {
    _gui.Add(std::make_unique<Button>(
        Vector2{400, 300},
        Vector2{100, 100},
        "Start",
        [this]() {
            stateMachine->ChangeState(std::make_unique<MapState>());
        }
    ));
}