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
    player.getSprite().setTexture("resources/player.png");
    player.getSprite().setPosition({400, 300});

    tree.setTexture("resources/tree.png");
    tree.setPosition({0, 0});
}