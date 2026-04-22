#pragma once

#include "../core/state.h"
#include "../raylib/raylib.h"
#include "../core/stateMachine.h"

#include "../entities/sprite.h"

#include "../battle/battleSystem.h"
#include "../battle/party.h"

#include "../battle/abilityUI.h"

class BattleState : public State {
    private:
        Texture2D _backgroundTexture;
        Sprite _background; 

        Texture2D _abilityIconTexture;

        // jsut for test
        Texture2D _characterTexture;
        std::unique_ptr<BattleEntity> _character;
        std::vector<AbilityUI> abilityIcons;


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