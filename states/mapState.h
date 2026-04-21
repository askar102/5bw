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
        Vector2 playerPos;

        Texture2D treeTexture;
        Texture2D playerTexture;

        Sprite tree;

        bool startBattle = false;

        std::vector<std::unique_ptr<Sprite>> trees;

        unsigned int currentTileX = 600;
        unsigned int currentTileY = 600;
        
        // todo: change to more safe method
        const int SCREEN_WIDTH = 800;
        const int SCREEN_HEIGHT = 600;

    public:
        void HandleInput() override;
        void Update(float dt) override;
        void Draw() override;

        void OnEnter() override;
        void OnExit() override;

        void LoadResources();
        void UnloadResources();
        
        void MapRotationCheck();
        void LoadTile();

        bool CheckCollision(Rectangle playerRect);

};