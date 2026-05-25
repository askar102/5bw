/**
 * @file menuState.h
 * @author askar102
 * @brief Menu scene
 * @date 2026-05-07
 * 
 * @copyright Copyright (c) 2026, askar102
 * 
 */

#pragma once

#include "../raylib/raylib.h"

#include "../core/state.h"
#include "../core/stateManager.h"

#include "../gui/button.h"
#include "../gui/guiManager.h"

#include "mapState.h"

class MenuState : public State {
public:
    void HandleInput() override;
    void Update(float dt) override;
    void Draw() override;
    void OnEnter() override;
    void OnExit() override;

    void InitGui();

private:
    bool startPressed = false;

    Button _startButton;

    GuiManager _gui;
};
