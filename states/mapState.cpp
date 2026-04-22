#include "mapState.h"
#include <memory>

void MapState::HandleInput() {
    if (IsKeyPressed(KEY_B)) {
        startBattle = true;
    }
}

void MapState::Draw() {
    ClearBackground(GREEN);
    DrawText("currentState: game(map)", 0, 0, 20, WHITE);
    // todo: delete this in future
    DrawText("NOTE: press B for battle", 0, 30, 20, WHITE);

    player.Draw();
    // tree.Draw();

    for (auto& tree : trees) {
        tree->Draw();
    }
}

void MapState::Update(float dt) {
    player.Update(dt, this);
    playerPos  = player.getSprite().getPosition();

    MapRotationCheck();

    if (startBattle && stateMachine) {
        startBattle = false;
        stateMachine->ChangeState(std::make_unique<BattleState>());
    }

    if (IsKeyPressed(KEY_H))
    {
        Sprite::SetDrawHitboxes(!Sprite::GetDrawHitboxes());
    }
}

void MapState::OnEnter() {
    this->LoadResources();

    player.getSprite().setPosition({400, 300});

    tree.setPosition({0, 0});

    LoadTile();
}

void MapState::OnExit() {
    this->UnloadResources();
}

void MapState::LoadResources() {
    playerTexture = LoadTexture("resources/player.png");
    player.getSprite().setTexture(&playerTexture);

    treeTexture = LoadTexture("resources/tree.png");
    tree.setTexture(&treeTexture);
}

void MapState::UnloadResources() {
    UnloadTexture(treeTexture);
    UnloadTexture(playerTexture);
}

void MapState::MapRotationCheck() {
    // up
    if (playerPos.y+100 < 0) {
        currentTileY += 1;
    
        LoadTile();
    
        player.getSprite().setPosition({playerPos.x, (float)SCREEN_HEIGHT});
    }

    // down
    if (playerPos.y > SCREEN_HEIGHT) {
        currentTileY -= 1;
    
        LoadTile();
    
        player.getSprite().setPosition({playerPos.x, 0});
    }

    // left
    if (playerPos.x+100 < 0) {
        currentTileX -= 1;
    
        LoadTile();
    
        player.getSprite().setPosition({(float)SCREEN_WIDTH, playerPos.y});
    }

    // right
    if (playerPos.x > SCREEN_WIDTH) {
        currentTileX += 1;
    
        LoadTile();
    
        player.getSprite().setPosition({0-100, playerPos.y});
    }
}

void MapState::LoadTile() {
    trees = MapGenerator::GenerateTile(
        "config.json",
        currentTileX,
        currentTileY,
        &treeTexture
    );
}

bool MapState::CheckCollision(Rectangle playerRect) {
    for (auto& tree : trees) {
        if (tree->getSolid()) {
            if (CheckCollisionRecs(playerRect, tree->getRect())) {
                return true;
            }
        }
    }
    return false;
}