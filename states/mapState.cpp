/**
 * @file mapState.cpp
 * @author askar102
 * @brief Map(world) scene
 * @date 2026-05-07
 * 
 * @copyright Copyright (c) 2026, askar102
 * 
 */

#include "mapState.h"

void MapState::HandleInput() {
    if (IsKeyPressed(KEY_B) && !startBattle) {
        startBattle = true;
    }

    if (IsKeyPressed(KEY_H))
    {
        SpriteV2::SetDrawHitboxes(!SpriteV2::GetDrawHitboxes());
        MapEntity::SetDrawZones(!MapEntity::GetDrawZones());
    }
}

void MapState::Draw() {
    ClearBackground(GREEN);

    for (auto& tree : trees) {
        tree->Draw();
    }

    for (Npc* npc : _activeNpcs)
    {
        npc->Draw();
    }
    
    player.Draw();

    // todo: delete this in future
    DrawText("currentState: game(map)", 0, 0, 20, WHITE);
    DrawText("NOTE: press B for battle", 0, 30, 20, WHITE);

    DrawText(TextFormat("X: %d, Y: %d", currentTileX, currentTileY), 0, 60, 20, WHITE);
    DrawText(TextFormat("mX: %d, mY: %d", GetMouseX(), GetMouseY()), 0, 90, 20, WHITE);
}

void MapState::Update(float dt) {
    player.Update(dt, this);
    playerPos  = player.getSprite().GetPosition();

    MapRotationCheck();

    if (startBattle && stateMachine) {
        startBattle = false;
        stateMachine->PushState(std::make_unique<BattleState>());
    }

    Vector2 playerPos = player.getSprite().GetPosition();
    for (Npc* npc : _activeNpcs)
    {
        npc->Update(dt, playerPos);
    }
}

void MapState::OnEnter() {
    this->LoadResources();

    player.getSprite().SetPosition({400, 300});
    
    // for player manipulation
    TileTrigger::SetPlayer(&player);

    TileTrigger::Init();

    LoadTile();
}

void MapState::OnExit() {}

void MapState::LoadResources() {
    player.getSprite().SetResource(&Game::GetResources().Get(TextureID::Player));

    tree.SetResource(&Game::GetResources().Get(TextureID::Tree));
    tree.SetSize({100, 100});
    tree.SetRectSize({90, 60});
}

void MapState::MapRotationCheck() {
    // old tile
    int prevX = currentTileX;
    int prevY = currentTileY;

    // up   
    if (playerPos.y+100 < 0) {
        currentTileY += 1;
    
        LoadTile();
    
        player.getSprite().SetPosition({playerPos.x, (float)SCREEN_HEIGHT});
    }

    // down
    if (playerPos.y > SCREEN_HEIGHT) {
        currentTileY -= 1;
    
        LoadTile();
    
        player.getSprite().SetPosition({playerPos.x, 0});
    }

    // left
    if (playerPos.x+100 < 0) {
        currentTileX -= 1;
    
        LoadTile();
    
        player.getSprite().SetPosition({(float)SCREEN_WIDTH, playerPos.y});
    }

    // right
    if (playerPos.x > SCREEN_WIDTH) {
        currentTileX += 1;
    
        LoadTile();
    
        player.getSprite().SetPosition({0-100, playerPos.y});
    }

    if (currentTileX != prevX || currentTileY != prevY) {
        TileTrigger::OnExitTile(prevX, prevY);
        TileTrigger::OnEnterTile(currentTileX, currentTileY);
    }
}

void MapState::LoadTile() {
    trees = MapGenerator::GenerateTile(
        "config.json",
        currentTileX,
        currentTileY,
        &Game::GetResources().Get(TextureID::Tree)
    );

    _activeNpcs = NpcManager::GetForTile(currentTileX, currentTileY);
}

bool MapState::CheckCollision(Rectangle playerRect) {
    for (auto& tree : trees) {
        if (tree->IsCollide()) {
            if (CheckCollisionRecs(playerRect, tree->GetRect())) {
                return true;
            }
        }
    }
    return false;
}