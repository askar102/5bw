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
    
    MapGenerator::ForEachChunk([this] (Chunk& c) {
        const auto& tiles = c.tiles;
        for (const auto& t : tiles) {
            t->sprite.Draw();
        }
    });

    for (Npc* npc : _activeNpcs)
    {
        npc->Draw();
    }

    MapItemManager::Draw();

    player.Draw();

    EndMode2D();

    _gui.Draw();
    
    // test
    testWrite.Draw();
    _dialog.Draw();

    // todo: delete this in future
    DrawText("currentState: game(map)", 0, 0, 20, WHITE);
    DrawText("NOTE: press B for battle", 0, 30, 20, WHITE);

    DrawText(TextFormat("tX: %d, tY: %d", currentTileX, currentTileY), 0, 60, 20, WHITE);
    DrawText(TextFormat("mX: %d, mY: %d", GetMouseX(), GetMouseY()), 0, 90, 20, WHITE);
    
    DrawText(TextFormat("cX: %d, cY: %d", currentChunkX, currentChunkY), 0, 120, 20, WHITE);
    
    std::string invStr;
    for (std::string itemTitle : Inventory::GetAsString()) {
       invStr += ", " + itemTitle; 
    }

    DrawText(TextFormat("inv: %s", invStr.c_str()), 0, 150, 20, WHITE);

}

void MapState::Update(float dt) {
    player.Update(dt, this);
    playerPos  = player.getSprite().GetPosition();

    _camera.target = player.getSprite().GetPosition();
    _worldMousePos = GetScreenToWorld2D(Game::GetWorldMouse(), _camera);

    // chunk position

    currentChunkX = (int)std::floor(playerPos.x / 624.0f);
    currentChunkY = -(int)std::floor(playerPos.y / 480.0f);

    // MapGenerator::GetChunk(currentChunkX, currentChunkY);

    MapGenerator::LoadDistantChunks(currentChunkX, currentChunkY, 3);
    MapGenerator::UnloadDistantChunks(currentChunkX, currentChunkY, 3);
    

    MapItemManager::Update(dt, player.getSprite());
    // _gui.Update();

    // MapRotationCheck();

    // battle
    if (startBattle && stateMachine) {
        startBattle = false;
        stateMachine->PushState(std::make_unique<BattleState>());
    }

    for (Npc* npc : _activeNpcs)
    {
        npc->Update(dt, {currentChunkX, currentChunkY, currentTileX, currentTileY});
    }

    Rectangle mouseRect = { _worldMousePos.x, _worldMousePos.y, 1.0f, 1.0f };

    MapGenerator::ForEachChunk([this, dt, mouseRect] (Chunk& c) {
        const auto& tiles = c.tiles;
        for (const auto& t : tiles) {
            t->sprite.Update(dt);

            if (CheckCollisionRecs(t->sprite.GetRect(), player.getSprite().GetRect())) {
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

    MapLocation curLoc{
        (int32_t)currentChunkX,
        (int32_t)currentChunkY,
        (int32_t)currentTileX,
        (int32_t)currentTileY
    };

    bool changed = !_prevLocInit || curLoc.chunkX != _prevLoc.chunkX || curLoc.chunkY != _prevLoc.chunkY;


    if (changed)
    {
        // if (_prevLocInit)
            // TileTrigger::OnExitTile(_prevLoc.tileX, _prevLoc.tileY);

        // LoadTile();
        // TileTrigger::OnEnterTile(curLoc.tileX, curLoc.tileY);


        _activeNpcs = NpcManager::GetForChunk(currentChunkX, currentChunkY);

        _prevLoc = curLoc;
        _prevLocInit = true;
    }

    testWrite.Update(dt);
    _dialog.Update(dt);
}

bool MapState::CheckTileCollision(Tile* tile) {
    if (tile->collide) {
        if (CheckCollisionRecs(tile->sprite.GetRect(), player.getSprite().GetRect())) {
            return true;
        }
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

    _activeNpcs = NpcManager::GetForChunk(currentChunkX, currentChunkY);

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

    auto testItem = std::make_unique<MapItem>(ItemID::Chalk, MapLocation{0, 0, 3, 3}, Game::GetResources().Get(TextureID::ItemIcons));

    MapItemManager::SpawnItem(ItemID::Chalk);
    MapItemManager::SpawnItem(ItemID::Kvass, {0, 1, 1, 0});

    NpcManager::Init();
    Dialog::Init();

    // test
    testWrite.SpawnAt((std::vector<std::string>){"huyyyyyyyyyyyyyyyyyy", "pizdaaaaaaaaaaaaaaaaaa"}, {100, 200});

    _dialog.Show(1, DialogMode::StoryCenter);
}

void MapState::OnExit() {}

void MapState::LoadResources() {
    player.getSprite().SetResource(&Game::GetResources().Get(TextureID::Player));

    tree.SetResource(&Game::GetResources().Get(TextureID::Tree));
    tree.SetSize({100, 100});
    tree.SetRectSize({90, 60});

    _mapTilesPack = Game::GetResources().Get(TextureID::MapTiles);
    MapGenerator::Init(&_mapTilesPack);

    Inventory::Init();

    _itemIconsPack = Game::GetResources().Get(TextureID::ItemIcons);
    MapItemManager::Init(&_itemIconsPack);

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

    _activeNpcs = NpcManager::GetForChunk(currentChunkX, currentChunkY);
}

bool MapState::CheckCollision(Rectangle playerRect) {
    bool collided = false;

    MapGenerator::ForEachChunk([&] (Chunk& c) {
        if (collided) return;

        const auto& tiles = c.tiles;
        for (const auto& t : tiles) {
            if (t->collide && CheckCollisionRecs(playerRect, t->sprite.GetRect())) {
                collided = true;
                return;
            }
        }
    });

    for (auto& npc : _activeNpcs) {
        if (npc->GetCollide() && CheckCollisionRecs(playerRect, npc->GetSprite().GetRect())) {
            collided = true;
            return collided;
        }
    }

    return collided;
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