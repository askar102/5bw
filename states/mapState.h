#pragma once

#include "../core/state.h"
#include "../raylib/raylib.h"
#include "../core/stateMachine.h"

#include "battleState.h"
#include "../entities/sprite.h"
#include "../entities/player.h"


class MapState : public State {
    private:
        Player player;

        Texture2D treeTexture;
        Texture2D playerTexture;

        Sprite tree;

        bool startBattle = false;

    public:
        void HandleInput() override;
        void Update(float dt) override;
        void Draw() override;

        void OnEnter() override;
        void OnExit() override;

        void LoadResources();
        void UnloadResources();

};