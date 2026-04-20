#pragma once

#include "../core/state.h"
#include "../raylib/raylib.h"
#include "../core/stateMachine.h"

#include "battleState.h"
#include "../entities/sprite.h"
#include "../entities/player.h"

#include "../misc/mapGenerator.h"

#include <vector>
#include <memory>

class MapState : public State {
    private:
        Player player;

        Texture2D treeTexture;
        Texture2D playerTexture;

        Sprite tree;

        bool startBattle = false;

        std::vector<std::unique_ptr<Sprite>> trees;

    public:
        void HandleInput() override;
        void Update(float dt) override;
        void Draw() override;

        void OnEnter() override;
        void OnExit() override;

        void LoadResources();
        void UnloadResources();

};