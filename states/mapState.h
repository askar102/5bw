/**
 * @file mapState.h
 * @author askar102
 * @brief Map(world) scene
 * @date 2026-05-07
 * 
 * @copyright Copyright (c) 2026, askar102
 * 
 */

#pragma once

#include <vector>
#include <memory>
#include <format>

#include "../raylib/raylib.h"

#include "../core/state.h"
#include "../core/game.h"
#include "../core/stateManager.h"

#include "../entities/spriteV2.h"
#include "../entities/player.h"
#include "../entities/uniqueHitbox.h"
#include "../entities/tree.h"

#include "../misc/mapGenerator.h"

#include "battleState.h"

class MapState : public State {
public:
    void HandleInput() override;
    void Update(float dt) override;
    void Draw() override;

    void OnEnter() override;
    void OnExit() override;

    void LoadResources();
        
    void MapRotationCheck();
    void LoadTile();

    bool CheckCollision(Rectangle playerRect);


private:
    Player player;
    Vector2 playerPos;

    SpriteV2 tree;

    bool startBattle = false;

    std::vector<std::unique_ptr<Tree>> trees;
                                                                                       
    unsigned int currentTileX = 600;
    unsigned int currentTileY = 600;
        
    // todo: change to more safe method
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;

};