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
                    _resources,
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
                AbilityManager::CardGuy::SpawnCardHeal(_resources, _vfxManager, *_character, *_enemy);
            }

            clickedAbility->Execute(*_character, *_enemy);
            _character->actionText.Add(TextFormat("Used %s", clickedAbility->getName().c_str()), YELLOW);
            _enemy->actionText.Add(TextFormat("Hit by %s", clickedAbility->getName().c_str()), ORANGE);
            return;
        }

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

void BattleState::Draw()
{
    ClearBackground(RED);

    _background.Draw();
    _character->Draw();
    _enemy->Draw();

    _vfxManager.Draw();

    _abilityPanel.Draw();

    DrawText("currentState: battle", 0, 0, 20, WHITE);
}

void BattleState::Update(float dt)
{
    _abilityPanel.SetVisible(_character->selected);
    _abilityPanel.SetAnchor(_character->getSprite().getPosition());
    _abilityPanel.Update();

    _vfxManager.Update(dt);
}

void BattleState::OnEnter()
{
    _character = std::make_unique<BattleEntity>();
    _enemy = std::make_unique<BattleEntity>();

    _character->abilities.push_back(std::make_unique<Ability>("CardAttack", 10, 0));
    _character->abilities.push_back(std::make_unique<Ability>("CardHeal"));
    _character->abilities.push_back(std::make_unique<Ability>("Heal", 0, 10));

    _resources.Load();

    InitBackground();

    _vfxManager.InitTextureManager(&_resources);

    _character->getSprite().setPosition({50, 300});
    _character->getSprite().setTexture(_resources.CharacterTexture());

    _enemy->getSprite().setPosition({600, 300});
    _enemy->getSprite().setTexture(_resources.EnemyTexture());
    _enemy->canSelected = false;
    _enemy->isEnemy = true;
    _enemy->getSprite().setSize(100, 100);
    _enemy->getSprite().changeSizeOfRect({100 , 100});

    _abilityPanel.SetIconTexture(_resources.AbilityIconTexture());
    _abilityPanel.SetAbilities(_character->abilities);
    _abilityPanel.SetAnchor(_character->getSprite().getPosition());
    _abilityPanel.SetVisible(false);
    _abilityPanel.Update();
}

void BattleState::OnExit()
{
    _vfxManager.Clear();
    _resources.Unload();
}

void BattleState::InitBackground()
{
    _background.setTexture(_resources.BackgroundTexture());
    _background.setSize(800, 600);
    _background.SetCanDrawHiboxes(false);
}
