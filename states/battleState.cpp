#include "battleState.h"

void BattleState::HandleInput() {
    Vector2 mouse = GetMousePosition();

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
    {
        if (CheckCollisionPointRec(mouse, _character->getSprite().getRect())) 
        {
            if (_character->canSelected) 
            {
                _character->selected = !_character->selected;
            }
        }
        else 
        {
            _character->selected = false;
        }
    }

    if (IsKeyPressed(KEY_H))
    {
        Sprite::SetDrawHitboxes(!Sprite::GetDrawHitboxes());
    }
}

void BattleState::Draw() {
    ClearBackground(RED);

    _background.Draw();
    
    // just for test
    _character->Draw();
    _enemy->Draw();

    _abilityPanel.Draw();

    DrawText("currentState: battle", 0, 0, 20, WHITE);
    // todo: delete this in future
    DrawText("NOTE: fcku, is last state", 0, 30, 20, WHITE);
}

void BattleState::Update(float dt) {
    (void)dt;

    _abilityPanel.SetVisible(_character->selected);
    _abilityPanel.SetAnchor(_character->getSprite().getPosition());
    _abilityPanel.Update();

    // if (startBattle) {
    //     // stateMachine->ChangeState(std::make_unique<GameState>());
    // }
}

void BattleState::OnEnter() {
    _character = std::make_unique<BattleEntity>();
    _enemy = std::make_unique<BattleEntity>();

    _character->abilities.push_back(std::make_unique<Ability>("Attack"));
    _character->abilities.push_back(std::make_unique<Ability>("Defend"));
    _character->abilities.push_back(std::make_unique<Ability>("Heal"));

    _resources.Load();

    // start logic
    InitBackground();

    // 50 x 300
    _character->getSprite().setPosition({50, 300});
    _character->getSprite().setTexture(_resources.CharacterTexture());

    _enemy->getSprite().setPosition({600, 300});
    _enemy->getSprite().setTexture(_resources.EnemyTexture());
    _enemy->canSelected = false;

    _abilityPanel.SetIconTexture(_resources.AbilityIconTexture());
    _abilityPanel.SetAbilities(_character->abilities);
    _abilityPanel.SetAnchor(_character->getSprite().getPosition());
    _abilityPanel.SetVisible(false);
    _abilityPanel.Update();


    // 0 - is first
    // party.Add(std::move(_character), 0);
    
}

void BattleState::OnExit() {
    _resources.Unload();
}

void BattleState::InitBackground()
{
    _background.setTexture(_resources.BackgroundTexture());
    _background.setSize(800, 600);
    _background.SetCanDrawHiboxes(false);
}