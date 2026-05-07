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

#include "mapState.h"

class MenuState : public State {
public:
    void HandleInput() override;
    void Update(float dt) override;
    void Draw() override;

private:
    bool startPressed = false;
};
