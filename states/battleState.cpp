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
    PlayerParty& party = Game::GetPlayerParty();

    Vector2 mouse = GetMousePosition();

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        BattleEntity* selectedCharacter = party.GetSelectedCharacter();

        if (selectedCharacter)
        {
            if (Ability* clickedAbility = _abilityPanel.GetAbilityAt(mouse))
            {
                const std::string abilityName = clickedAbility->GetName();

                AbilityManager::SpawnAbility(
                    *clickedAbility,
                    _vfxManager,
                    *selectedCharacter,
                    *_enemyParty.Get(0)
                );

                selectedCharacter->actionText.Add(TextFormat("Used %s", clickedAbility->GetName().c_str()), YELLOW);
                // todo: change
                _enemyParty.Get(0)->actionText.Add(TextFormat("Hit by %s", clickedAbility->GetName().c_str()), ORANGE);

                party.DeselectAll();

                return;
            } 
        }

        party.UpdateSelection();
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
    _enemyParty.Get(0)->Draw();

    PlayerParty& playerParty = Game::GetPlayerParty();
    for (size_t i = 0; i < 4; ++i)
    {
        BattleEntity* character = playerParty.Get(i);

        if (character)
        {
            character->Draw();
        }
    }   

    _vfxManager.Draw();

    _abilityPanel.Draw();

    DrawText("currentState: battle", 0, 0, 20, WHITE);
    DrawText(TextFormat("mX: %d, mY: %d", GetMouseX(), GetMouseY()), 0, 30, 20, WHITE);
}

void BattleState::Update(float dt)
{
    PlayerParty& party = Game::GetPlayerParty();

    BattleEntity* selected =
        party.GetSelectedCharacter();

    // update party characters

    for (size_t i = 0; i < 4; ++i)
    {
        BattleEntity* character = party.Get(i);

        if (character)
        {
            character->Update(dt);
        }
    }

    // ability panel

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

    _enemyParty.Get(0)->Update(dt);
    _vfxManager.Update(dt);
}

void BattleState::OnEnter()
{
    PlayerParty& playerParty = Game::GetPlayerParty();
    for (size_t i = 0; i < 4; ++i)
    {
        BattleEntity* character = playerParty.Get(i);

        if (character)
        {
            TraceLog(LOG_INFO, "[PARTY] character: %s", character->name.c_str());

            character->getSprite().SetResource(&Game::GetResources().Get(character->name));

            TraceLog(LOG_INFO, "[PARTY] character: %s", character->name.c_str());
            for (const auto& ab : character->abilities)
            {
                TraceLog(LOG_INFO, "[PARTY] ---characterAbilities: %s", ab->GetName().c_str());
            }

        }
        else
        {      
            TraceLog(LOG_INFO, "[PARTY] empty slot");
        }
    }   

    // _enemy = std::make_unique<BattleEntity>((BattleEntity){"name", 100, false, true, {}});

    InitBackground();

    _enemyParty.Init();

    // _enemy->getSprite().SetPosition({570, 400});
    // _enemy->getSprite().SetResource(&Game::GetResources().Get(TextureID::Enemy));
    // _enemy->canSelected = false;
    // _enemy->isEnemy = true;
    // _enemy->getSprite().SetSize({100, 100});
    // _enemy->getSprite().SetRectSize({100 , 100});

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
