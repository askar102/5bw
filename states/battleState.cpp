#include "battleState.h"

void BattleState::HandleInput() {
    Vector2 mouse = GetMousePosition();

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
    {
        if (CheckCollisionPointRec(mouse, _character->getSprite().getRect())) 
        {
            _character->selected = !_character->selected;
        }
        else 
        {
            _character->selected = false;
        }
    }
}

void BattleState::Draw() {
    ClearBackground(RED);

    _background.Draw();
    
    // just for test
    _character->Draw();

    DrawText("currentState: battle", 0, 0, 20, WHITE);
    // todo: delete this in future
    DrawText("NOTE: fcku, is last state", 0, 30, 20, WHITE);
}

void BattleState::Update(float dt) {
    // if (startBattle) {
    //     // stateMachine->ChangeState(std::make_unique<GameState>());
    // }
}

void BattleState::OnEnter() {
    _character = std::make_unique<BattleEntity>();
    this->LoadResources();

    // start logic
    _background.setSize(800, 600);

    // 50 x 300
    _character->getSprite().setPosition({50, 300});

    // 0 - is first
    // party.Add(std::move(_character), 0);
    
}

void BattleState::OnExit() {
    this->UnloadResources();
}

void BattleState::LoadResources() {
    _backgroundTexture = LoadTexture("resources/battle.png");
    _background.setTexture(&_backgroundTexture);

     // just for test
    _characterTexture = LoadTexture("resources/player.png");
    _character->getSprite().setTexture(&_characterTexture);
}

void BattleState::UnloadResources() {
    UnloadTexture(_backgroundTexture);
    UnloadTexture(_characterTexture);
}