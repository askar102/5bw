#pragma once

#include "../core/state.h"
#include "../raylib/raylib.h"
#include "../core/stateMachine.h"

#include "../entities/sprite.h"

#include "../battle/battleSystem.h"
#include "../battle/party.h"

class BattleState : public State {
    private:
        Texture2D _backgroundTexture;
        Sprite _background; 

        // jsut for test
        Texture2D _characterTexture;
        std::unique_ptr<BattleEntity> _character;

        Party party;


    public:
        void HandleInput() override;
        void Update(float dt) override;
        void Draw() override;

        void OnEnter() override;
        void OnExit() override;

        void LoadResources();
        void UnloadResources();
};