#pragma once

#include "../core/state.h"
#include "../raylib/raylib.h"
#include "../core/stateMachine.h"

#include "battleState.h"
#include "../entities/sprite.h"

class MapState : public State {
    private:
        bool startBattle = false;
        Sprite player;

    public:
        void HandleInput() override;
        void Update(float dt) override;
        void Draw() override;

};