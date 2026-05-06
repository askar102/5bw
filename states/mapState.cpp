#include "mapState.h"

void MapState::HandleInput() {
    if (IsKeyPressed(KEY_B)) {
        startBattle = true;
    }
}

void MapState::Draw() {
    ClearBackground(GREEN);
    // tree.Draw();

    for (auto& tree : trees) {
        tree->Draw();
    }

    player.Draw();

    // todo: delete this in future
    DrawText("currentState: game(map)", 0, 0, 20, WHITE);
    DrawText("NOTE: press B for battle", 0, 30, 20, WHITE);

    DrawText(TextFormat("X: %d, Y: %d", currentTileX, currentTileY), 0, 60, 20, WHITE);
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

void MapState::OnExit() {}

void MapState::LoadResources() {
    player.getSprite().setTexture(&Game::GetResources().Get(TextureID::Player).texture);

    tree.setTexture(&Game::GetResources().Get(TextureID::Tree).texture);
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
        &Game::GetResources().Get(TextureID::Tree).texture
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