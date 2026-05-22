/**
 * @file battleState.cpp
 * @author askar102
 * @brief Battle scene
 * @date 2026-05-07
 * 
 * @copyright Copyright (c) 2026, askar102
 * 
 */

#include "battleState.h"

void BattleState::HandleInput()
{
    Vector2 mouse = GetMousePosition();

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        BattleEntity* selectedCharacter = _partyManager.GetSelectedCharacter();

        if (selectedCharacter)
        {
            if (Ability* clickedAbility = _abilityPanel.GetAbilityAt(mouse))
            {
                BattleEntity* target = _partyManager.GetEnemy(0);

                if (target)
                {
                    AbilityManager::SpawnAbility(
                        *clickedAbility,
                        _vfxManager,
                        *selectedCharacter,
                        *target
                    );
                } 

                
                selectedCharacter->actionText.Add(TextFormat("Uzanulo %s", clickedAbility->GetName().c_str()), YELLOW);
                // todo: change
                target->actionText.Add(TextFormat("Pizdanulo by %s", clickedAbility->GetName().c_str()), ORANGE);

                _partyManager.DeselectAll();

                return;
            } 
        }

        _partyManager.UpdateSelection();
    }

    if (IsKeyPressed(KEY_H))
    {
        SpriteV2::SetDrawHitboxes(!SpriteV2::GetDrawHitboxes());
    }
}

void BattleState::Draw()
{
    ClearBackground(RED);

    _background.Draw();
    _partyManager.Draw(); 
    _vfxManager.Draw();
    _abilityPanel.Draw();

    DrawText("currentState: battle", 0, 0, 20, WHITE);
    DrawText(TextFormat("mX: %d, mY: %d", GetMouseX(), GetMouseY()), 0, 30, 20, WHITE);
}

void BattleState::Update(float dt)
{
    _partyManager.Update(dt);

    BattleEntity* selected = _partyManager.GetSelectedCharacter();

    if (selected)
    {
        _abilityPanel.SetVisible(true);
        _abilityPanel.SetAnchor(selected->getSprite().GetPosition());
        _abilityPanel.SetAbilities(selected->abilities);
    }
    else
    {
        _abilityPanel.SetVisible(false);
    }

    _abilityPanel.Update();
    _vfxManager.Update(dt);
}

void BattleState::OnEnter()
{
    InitBackground();

    _partyManager.Init();

    InitPlayerParty();
    InitEnemyParty();

    _abilityPanel.SetIconTexture(&Game::GetResources().Get(TextureID::AbilityIcon));
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

void BattleState::InitPlayerParty()
{
    for (size_t i = 0; i < 4; ++i)
    {
        BattleEntity* character = _partyManager.GetPlayer(i);

        if (!character) continue;

        TraceLog(LOG_INFO, "[PARTY] character: %s", character->name.c_str());
        character->getSprite().SetResource(&Game::GetResources().Get(character->name));

        for (const auto& ab : character->abilities)
            TraceLog(LOG_INFO, "[PARTY] ---ability: %s", ab->GetName().c_str());
    }
}

void BattleState::InitEnemyParty()
{
    for (size_t i = 0; i < 4; ++i)
    {
        BattleEntity* enemy = _partyManager.GetEnemy(i);
        if (!enemy) continue;

        TraceLog(LOG_INFO, "[ENEMY PARTY] enemy: %s", enemy->name.c_str());
        enemy->getSprite().SetResource(&Game::GetResources().Get(TextureID::Enemy));
        enemy->getSprite().SetSize({100, 100});
        enemy->getSprite().SetRectSize({100, 100});
    }
}