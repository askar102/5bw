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
    player.Update(dt);

    if (startBattle && stateMachine) {
        startBattle = false;
        stateMachine->ChangeState(std::make_unique<BattleState>());
    }
}

void MapState::OnEnter() {
    this->LoadResources();

    player.getSprite().setPosition({400, 300});

    tree.setPosition({0, 0});

    // delete, just for test
    Vector2 pos{0,0};
    const int cols = 8;
    const int rows = 8;


    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++){
            auto tree = std::make_unique<Sprite>();

            tree->setTexture(&treeTexture);
            tree->setSize(100, 100);
            tree->setPosition(pos);

            if (!trees.empty()) {
                tree->setPosition({
                    x * trees.back()->getSize().x,
                    y * trees.back()->getSize().y
                });
            }
        
            trees.push_back(std::move(tree));
        }
    }
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