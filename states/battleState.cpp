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
    Party& party = Game::GetPlayerParty();

    BattleEntity* selectedCharacter = party.GetSelectedCharacter();

    Vector2 mouse = GetMousePosition();

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        if (selectedCharacter)
        {
            if (Ability* clickedAbility = _abilityPanel.GetAbilityAt(mouse))
            {
                const std::string abilityName = clickedAbility->GetName();

                AbilityManager::SpawnAbility(
                    *clickedAbility,
                    _vfxManager,
                    *selectedCharacter,
                    *_enemy
                );

                selectedCharacter->actionText.Add(TextFormat("Used %s", clickedAbility->GetName().c_str()), YELLOW);
                // todo: change
                _enemy->actionText.Add(TextFormat("Hit by %s", clickedAbility->GetName().c_str()), ORANGE);

                return;
            } 
        }
        party.UpdateSelection();

        if (IsKeyPressed(KEY_H))
        {
            SpriteV2::SetDrawHitboxes(!SpriteV2::GetDrawHitboxes());
        }
    }
}

void BattleState::Draw()
{
    ClearBackground(RED);

    _background.Draw();
    _enemy->Draw();

    Party& playerParty = Game::GetPlayerParty();
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
    Party& party = Game::GetPlayerParty();

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

    _enemy->Update(dt);
    _vfxManager.Update(dt);
}

void BattleState::OnEnter()
{
    Party& playerParty = Game::GetPlayerParty();
    for (size_t i = 0; i < 4; ++i)
    {
        BattleEntity* character = playerParty.Get(i);

        if (character)
        {
            TraceLog(LOG_INFO, "[PARTY] character: %s", character->name.c_str());

            character->getSprite().SetResource(&Game::GetResources().Get(character->name));

            for (const auto& ab : character->abilities)
            {
                TraceLog(LOG_INFO, "---characterAbilities: %s", ab->GetName().c_str());
            }

        }
        else
        {      
            TraceLog(LOG_INFO, "[PARTY] empty slot");
        }
    }   

    _character = std::make_unique<BattleEntity>((BattleEntity){"name", 100, false, true, {}});
    _enemy = std::make_unique<BattleEntity>((BattleEntity){"name", 100, false, true, {}});

    // abiityName, damage, heal
    _character->abilities.push_back(std::make_unique<Ability>("CardAttack", 10, 0));
    _character->abilities.push_back(std::make_unique<Ability>("CardHeal", 0, 25));
    _character->abilities.push_back(std::make_unique<Ability>("CardBlock", 0, 10));


    InitBackground();

    _character->getSprite().SetPosition({120, 400});
    _character->getSprite().SetResource(&Game::GetResources().Get(TextureID::CardGuy));
    _character->getSprite().SetFrame(0);

    _enemy->getSprite().SetPosition({570, 400});
    _enemy->getSprite().SetResource(&Game::GetResources().Get(TextureID::Enemy));
    _enemy->canSelected = false;
    _enemy->isEnemy = true;
    _enemy->getSprite().SetSize({100, 100});
    _enemy->getSprite().SetRectSize({100 , 100});

    _abilityPanel.SetIconTexture(&Game::GetResources().Get(TextureID::AbilityIcon));
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
