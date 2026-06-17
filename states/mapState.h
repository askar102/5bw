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

#include <cstdint>
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

#include "../map/npc.h"

#include "../map/npcManager.h"
#include "../map/tileTrigger.h"

// For init font
#include "../dialog/dialogPopup.h"

#include "../gui/button.h"
#include "../gui/guiManager.h"

#include "../gui/window.h"

// items
#include "../map/mapItem.h"

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
    bool CheckTileCollision(Tile* tile);

    Vector2 GetCurrentTilePos() const { return {static_cast<float>(currentTileX), static_cast<float>(currentTileY)}; }

    // gui flow
    void InitGui();
    std::vector<std::unique_ptr<Button>> GetInventoryButtons();

private:
    Player player;
    Vector2 playerPos;

    SpriteV2 tree;

    bool startBattle = false;

    std::vector<std::unique_ptr<Tree>> trees;

    uint32_t currentChunkX = 0;
    uint32_t currentChunkY = 0;

    uint32_t currentTileX = 0;
    uint32_t currentTileY = 0;
        
    const int SCREEN_WIDTH = GetScreenWidth();
    const int SCREEN_HEIGHT = GetScreenHeight();


    std::vector<Npc*> _activeNpcs; 

    GuiManager _gui;

    // new

    TextureResource _mapTilesPack; 
    TextureResource _itemIconsPack;

    // builder mode
    bool _builderMode = false;

    Camera2D _camera;
    Vector2 _worldMousePos = GetScreenToWorld2D(Game::GetWorldMouse(), _camera);

};