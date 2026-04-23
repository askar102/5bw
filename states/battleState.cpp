#include "battleState.h"
#include <algorithm>

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


    if (_character->selected)
    {
        for (auto& ui : abilityIcons)
        {
            ui.icon.Draw();

            if (ui.ability)
            {
                DrawText(
                    ui.ability->name.c_str(),
                    ui.pos.x + 10,   // смещение внутри кнопки
                    ui.pos.y + 10,
                    20,
                    WHITE
                );
        }
        }
    }
}

void BattleState::Update(float dt) {
    (void)dt;

    Vector2 basePos = _character->getSprite().getPosition();
    for (size_t i = 0; i < abilityIcons.size(); ++i)
    {
        abilityIcons[i].pos = {basePos.x + 90.0f, basePos.y + (float)i * 50.0f};
        abilityIcons[i].icon.setPosition(abilityIcons[i].pos);
    }

    // if (startBattle) {
    //     // stateMachine->ChangeState(std::make_unique<GameState>());
    // }
}

void BattleState::OnEnter() {
    _character = std::make_unique<BattleEntity>();

    _character->abilities.push_back(std::make_unique<Ability>("Attack"));
    _character->abilities.push_back(std::make_unique<Ability>("Defend"));
    _character->abilities.push_back(std::make_unique<Ability>("Heal"));

    this->LoadResources();

    // start logic
    _background.setSize(800, 600);

    // 50 x 300
    _character->getSprite().setPosition({50, 300});

    abilityIcons.clear();
    abilityIcons.reserve(3);

    const size_t maxAbilities = std::min<size_t>(_character->abilities.size(), 3);
    Vector2 basePos = _character->getSprite().getPosition();

    for (size_t i = 0; i < maxAbilities; ++i)
    {
        auto& ability = _character->abilities[i];
        AbilityUI ui;
        ui.ability = ability.get();
        ui.icon.setTexture(&AbilityUI::defaultTexture);
        ui.pos = {basePos.x + 90.0f, basePos.y + (float)i * 50.0f};
        ui.icon.setPosition(ui.pos);

        abilityIcons.push_back(ui);
    }


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

    AbilityUI::defaultTexture = LoadTexture("resources/option.png");

}

void BattleState::UnloadResources() {
    UnloadTexture(_backgroundTexture);
    UnloadTexture(_characterTexture);
    UnloadTexture(AbilityUI::defaultTexture);
}