#pragma once

#include "../core/state.h"
#include "../raylib/raylib.h"
#include "../core/stateMachine.h"

class MenuState : public State {
    private:
        bool startPressed = false;

    public:
        void HandleInput() override;
        void Update(float dt) override;
        void Draw() override;

};