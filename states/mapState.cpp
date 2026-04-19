#include "mapState.h"

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
    tree.Draw();
}

void MapState::Update(float dt) {
    player.Update(dt);

    if (startBattle && stateMachine) {
        startBattle = false;
        stateMachine->ChangeState(std::make_unique<BattleState>());
    }
}

void MapState::OnEnter() {
    this->LoadResources();

    player.getSprite().setPosition({400, 300});
    player.getSprite().setSize(100, 100);

    tree.setPosition({0, 0});
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