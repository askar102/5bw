#pragma once

#include "../core/state.h"
#include "../raylib/raylib.h"
#include "../core/stateMachine.h"

class BattleState : public State {
    private:
        // pass


    public:
        void HandleInput() override;
        void Update(float dt) override;
        void Draw() override;
};