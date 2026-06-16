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
#include <cstdint>
#include <memory>

void MapState::HandleInput() {
    if (IsKeyPressed(KEY_B) && !startBattle) {
        startBattle = true;
    }

    if (IsKeyPressed(KEY_H))
    {
        SpriteV2::SetDrawHitboxes(!SpriteV2::GetDrawHitboxes());
        MapEntity::SetDrawZones(!MapEntity::GetDrawZones());
    }

    if (IsKeyPressed(KEY_V))
    {
        _builderMode = !_builderMode;
    }
}

void MapState::Draw() {
    ClearBackground(BLACK);

    BeginMode2D(_camera);

    for (auto& tree : trees) {
        tree->Draw();
    }

    for (Npc* npc : _activeNpcs)
    {
        npc->Draw();
    }
    
    MapGenerator::ForEachChunk([this] (Chunk& c) {
        const auto& tiles = c.tiles;
        for (const auto& t : tiles) {
            t->sprite.Draw();
        }
    });

    player.Draw();

    EndMode2D();

    _gui.Draw();

    // todo: delete this in future
    DrawText("currentState: game(map)", 0, 0, 20, WHITE);
    DrawText("NOTE: press B for battle", 0, 30, 20, WHITE);

    DrawText(TextFormat("tX: %d, tY: %d", currentTileX, currentTileY), 0, 60, 20, WHITE);
    DrawText(TextFormat("mX: %d, mY: %d", GetMouseX(), GetMouseY()), 0, 90, 20, WHITE);
    
    DrawText(TextFormat("cX: %d, cY: %d", currentChunkX, currentChunkY), 0, 120, 20, WHITE);
    
}

void MapState::Update(float dt) {
    player.Update(dt, this);
    playerPos  = player.getSprite().GetPosition();

    _camera.target = player.getSprite().GetPosition();
    _worldMousePos = GetScreenToWorld2D(Game::GetWorldMouse(), _camera);

    // chunk position
    currentChunkX = -(int)std::floor(playerPos.x / 624.0f);
    currentChunkY = -(int)std::floor(playerPos.y / 480.0f);

    // MapGenerator::GetChunk(currentChunkX, currentChunkY);

    MapGenerator::LoadDistantChunks(currentChunkX, currentChunkY, 3);
    MapGenerator::UnloadDistantChunks(currentChunkX, currentChunkY, 3);
    
    // _gui.Update();

    // MapRotationCheck();

    // battle
    if (startBattle && stateMachine) {
        startBattle = false;
        stateMachine->PushState(std::make_unique<BattleState>());
    }

    // Vector2 playerPos = player.getSprite().GetPosition();
    // for (Npc* npc : _activeNpcs)
    // {
    //     npc->Update(dt, playerPos);
    // }

    Rectangle mouseRect = { _worldMousePos.x, _worldMousePos.y, 1.0f, 1.0f };

    MapGenerator::ForEachChunk([this, dt, mouseRect] (Chunk& c) {
        const auto& tiles = c.tiles;
        for (const auto& t : tiles) {
            t->sprite.Update(dt);

            if (CheckTileCollision(t.get())) {
                currentTileX = t->x;
                currentTileY = t->y;
            } 

             // BUILDER MODE LOGIC
            if (_builderMode) {

                if (CheckCollisionRecs(t->sprite.GetRect(), mouseRect)) {
                    t->sprite.SetBrightness(1.5f);
                }
                else
                {
                    t->sprite.SetBrightness(1.0f);
                } 
            }
            else t->sprite.SetBrightness(1.0f); 
        }
    });
}

bool MapState::CheckTileCollision(Tile* tile) {
    if (CheckCollisionRecs(tile->sprite.GetRect(), player.getSprite().GetRect())) {
        return true;
    }

    return false;
}

void MapState::OnEnter() {
    this->LoadResources();

    player.getSprite().SetPosition({SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f});
    player.getSprite().SetSize({48, 48});

    _camera.target = player.getSprite().GetPosition();
    _camera.offset = { SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f };
    _camera.rotation = 0.0f;
    _camera.zoom = 1.0f;

    // InitGui();

    // // for player manipulation
    // TileTrigger::SetPlayer(&player);

    // TileTrigger::Init();
    // DialogPopup::Init();

    // LoadTile();

    Vector2 startPos = {0, 0};
    // 26, 15 - full map
    // for (int tx = 0; tx <= 13; ++tx) {
    //     for (int ty = 0; ty <= 10; ++ty) {
    //         // tree checker
    //         if (tx == 12 && ty == 6) {
    //             auto tile = std::make_unique<Tile>();
    //             tile->sprite.SetResource(&tileTx);
    //             tile->sprite.SetFrame(1);

    //             tile->x = tx;
    //             tile->y = ty;

    //             tile->sprite.SetPosition({
    //                 startPos.x + (float)tx * 48.0f + 48.0f / 2,
    //                 startPos.y + (float)ty * 48.0f + 48.0f / 2
    //             });

    //             tiles.push_back(std::move(tile));
    //             continue;
    //         }


    //         auto tile = std::make_unique<Tile>();
    //         tile->sprite.SetResource(&tileTx);
    //         tile->sprite.SetFrame(0);

    //         tile->x = tx;
    //         tile->y = ty;

    //         tile->sprite.SetPosition({
    //             startPos.x + (float)tx * 48.0f + 48.0f / 2,
    //             startPos.y + (float)ty * 48.0f + 48.0f / 2
    //         });

    //         tiles.push_back(std::move(tile));
    //     }
    // }

    MapGenerator::GetChunk(currentChunkX, currentChunkY);
}

void MapState::OnExit() {}

void MapState::LoadResources() {
    player.getSprite().SetResource(&Game::GetResources().Get(TextureID::Player));

    tree.SetResource(&Game::GetResources().Get(TextureID::Tree));
    tree.SetSize({100, 100});
    tree.SetRectSize({90, 60});


    _mapTilesPack = Game::GetResources().Get(TextureID::MapTiles);
    MapGenerator::Init(&_mapTilesPack);

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
    // trees = MapGenerator::GenerateTile(
    //     "config.json",
    //     currentTileX,
    //     currentTileY,
    //     &Game::GetResources().Get(TextureID::Tree)
    // );

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

void MapState::InitGui()
{ 
    auto menuButton = std::make_unique<Button>(
        Vector2{767, 50},
        Vector2{50, 50},
        "",
        &Game::GetResources().Get("gameMenuButton"),
        [this]() {
            printf("Pizda menu\n");
        },
        PositionType::Left
    );

    menuButton->GetSprite().SetAlpha(0.5f);

    _gui.Add(std::move(menuButton));

    auto inventoryButton = std::make_unique<Button>(
        Vector2{767, 110},
        Vector2{50, 50},
        "",
        &Game::GetResources().Get("inventoryButton"),
        [this]() {
            printf("pizda inv\n");
        },
        PositionType::Left
    );
    
    inventoryButton->GetSprite().SetAlpha(0.5f);                                                                

    Button* rawInvButtonPtr = inventoryButton.get();

    _gui.Add(std::move(inventoryButton));   

    // invetnrory window
    auto inventoryWindow = std::make_unique<Window>(rawInvButtonPtr);

    // invWindow buttons
    inventoryWindow->AddButtons(GetInventoryButtons());

    _gui.Add(std::move(inventoryWindow));

}

std::vector<std::unique_ptr<Button>> MapState::GetInventoryButtons()
{
    std::vector<std::unique_ptr<Button>> buttons;

    // party window
    auto changePartyButton = std::make_unique<Button>(
        Vector2{400 - 100, 300 + 100},
        Vector2{150, 60},
        "",
        &Game::GetResources().Get("changePartyButton"),
        [this]() {
            printf("change party\n");
        },
        PositionType::Left
    );

    buttons.push_back(std::move(changePartyButton));


    // book window
    auto changeBookButton = std::make_unique<Button>(
        Vector2{400 + 100, 300 + 100},
        Vector2{150, 60},
        "",
        &Game::GetResources().Get("changeBookButton"),
        [this] () {
            printf("change book\n");
        },
        PositionType::Left
    );

    buttons.push_back(std::move(changeBookButton));

    return buttons;
}