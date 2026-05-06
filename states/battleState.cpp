#include "battleState.h"
#include "../battle/abilityManager.h"

void BattleState::HandleInput()
{
    Vector2 mouse = GetMousePosition();

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        if (Ability* clickedAbility = _abilityPanel.GetAbilityAt(mouse))
        {
            _character->selected = false;

            const std::string abilityName = clickedAbility->getName();

            if (abilityName == "CardAttack")
            {
                AbilityManager::CardGuy::SpawnCardAttack(
                    _vfxManager,
                    *_character,
                    *_enemy,
                    clickedAbility->getDamage()
                );
                /**
                 * @ref we damage enemy at cardVfx.cpp, ~35 line
                 * 
                 */
                clickedAbility->Execute(*_character, *_enemy, true);
                _character->actionText.Add(TextFormat("Used %s", clickedAbility->getName().c_str()), YELLOW);
                _enemy->actionText.Add(TextFormat("Hit by %s", clickedAbility->getName().c_str()), ORANGE);
                return;
            }

            if (abilityName == "CardHeal")
            {
                AbilityManager::CardGuy::SpawnCardHeal( _vfxManager, *_character, *_enemy);
                clickedAbility->Execute(*_character, *_enemy);
            }

            if (abilityName == "CardBlock")
            {
                AbilityManager::CardGuy::SpawnCardBlock(_vfxManager, *_character, *_enemy);
            }

            clickedAbility->Execute(*_character, *_enemy);
            _character->actionText.Add(TextFormat("Used %s", clickedAbility->getName().c_str()), YELLOW);
            _enemy->actionText.Add(TextFormat("Hit by %s", clickedAbility->getName().c_str()), ORANGE);
            return;
        }

        if (CheckCollisionPointRec(mouse, _character->getSprite().GetRect()))
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

void BattleState::Draw()
{
    ClearBackground(RED);

    _background.Draw();
    _character->Draw();
    _enemy->Draw();

    _vfxManager.Draw();

    _abilityPanel.Draw();

    DrawText("currentState: battle", 0, 0, 20, WHITE);
    DrawText(TextFormat("mX: %d, mY: %d", GetMouseX(), GetMouseY()), 0, 30, 20, WHITE);
}

void BattleState::Update(float dt)
{
    _abilityPanel.SetVisible(_character->selected);
    _abilityPanel.SetAnchor(_character->getSprite().GetPosition());
    _abilityPanel.Update();

    _vfxManager.Update(dt);
}

void BattleState::OnEnter()
{
    _character = std::make_unique<BattleEntity>();
    _enemy = std::make_unique<BattleEntity>();

    // abiityName, damage, heal
    _character->abilities.push_back(std::make_unique<Ability>("CardAttack", 10, 0));
    _character->abilities.push_back(std::make_unique<Ability>("CardHeal", 0, 25));
    _character->abilities.push_back(std::make_unique<Ability>("CardBlock", 0, 10));


    InitBackground();

    _character->getSprite().SetPosition({50, 300});
    _character->getSprite().SetResource(&Game::GetResources().Get(TextureID::CardGuyAtlas));
    _character->getSprite().SetFrame(0);

    _enemy->getSprite().SetPosition({600, 300});
    _enemy->getSprite().SetResource(&Game::GetResources().Get(TextureID::Enemy));
    _enemy->canSelected = false;
    _enemy->isEnemy = true;
    _enemy->getSprite().SetSize({100, 100});
    _enemy->getSprite().SetRectSize({100 , 100});

    _abilityPanel.SetIconTexture(&Game::GetResources().Get(TextureID::AbilityIcon).texture);
    _abilityPanel.SetAbilities(_character->abilities);
    _abilityPanel.SetAnchor(_character->getSprite().GetPosition());
    _abilityPanel.SetVisible(false);
    _abilityPanel.Update();
}

void BattleState::OnExit()
{
    _vfxManager.Clear();
}

void BattleState::InitBackground()
{
    _background.SetResource(&Game::GetResources().Get(TextureID::BattleBg));
    _background.SetSize({800, 600});
    _background.SetPosition({(float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2});
    _background.SetCanDrawHiboxes(false);
}
