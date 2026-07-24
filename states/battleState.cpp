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
#include "../misc/inputBridge.h"
#include "../external/json.h"

BattleState* BattleState::s_active = nullptr;

void BattleState::HandleInput()
{
    Vector2 mouse = Game::GetWorldMouse();

    if (_targetSelector.IsActive())
    {
        _targetSelector.HandleInput(mouse);
        return;
    }


    if (InputBridge::MouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        // target flow
        if (Ability* clickedAbility = _abilityPanel.GetAbilityAt(mouse))
        {
            BattleEntity* selected = _partyManager.GetSelectedEntity();
            if (!selected) return;

            if (clickedAbility->GetType() == AbilityType::Target)
            {
                _targetSelector.Arm(
                    selected,
                    GatherAllTargets(),
                    AbilityManager::MakeTargetDesc(
                        *clickedAbility,
                        _vfxManager,
                        _partyManager,
                        stateMachine
                    )
                );
                _partyManager.DeselectAll();
                return;
            }

            BattleEntity* target = _partyManager.GetAbilityTarget(*selected);
            if (target)
            {
                AbilityManager::SpawnAbility(
                    *clickedAbility,
                    _vfxManager,
                    *selected,
                    *target,
                    _partyManager,
                    stateMachine
                );
 
                selected->actionText.Add(TextFormat("Uzanulo %s", clickedAbility->GetName().c_str()), YELLOW);
                target->actionText.Add(TextFormat("Pizdanulo by %s", clickedAbility->GetName().c_str()), ORANGE);
            }

            _partyManager.DeselectAll();
            return;

        }
        _partyManager.UpdateSelection();
    }

    if (InputBridge::KeyPressed(KEY_H))
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

    if (_targetSelector.IsActive())
        _targetSelector.Draw(Game::GetWorldMouse());


    if (_partyManager.isTimeStopped())
    {
        DrawRectangle(0, 0, (int)Game::GetVirtualPos().x, (int)Game::GetVirtualPos().y, Fade(GRAY, 0.5));
    }

    DrawText("currentState: battle", 0, 0, 20, WHITE);
    DrawText(TextFormat("mX: %d, mY: %d", GetMouseX(), GetMouseY()), 0, 30, 20, WHITE);
}

void BattleState::Update(float dt)
{
    _partyManager.Update(dt);

    BattleEntity* selected = _partyManager.GetSelectedEntity();

    if (selected)
    {
        const float panelOffset = (selected->facing == FacingDirection::Left) ? -150.0f : 150.0f;

        _abilityPanel.SetVisible(true);
        //то есть теперь мы принимаем оффсет положения стороны перса
        _abilityPanel.SetAnchor(selected->getSprite().GetPosition(), panelOffset);
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
    s_active = this;

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

    if (_targetSelector.IsActive())
        _targetSelector.Cancel();

    if (s_active == this)
        s_active = nullptr;
}

void BattleState::InitBackground()
{
    _background.SetResource(&Game::GetResources().Get(TextureID::BattleBg));
    _background.SetSize({Game::GetVirtualPos().x, Game::GetVirtualPos().y});
    _background.SetPosition({Game::GetVirtualPos().x / 2, Game::GetVirtualPos().y / 2});
    _background.SetCanDrawHiboxes(false);
}

// test-only: dumps battle state as JSON for Playwright assertions
// without having to screenshot+eyeball HP bars.
std::string BattleState::DumpTestState()
{
    nlohmann::json j;
    j["timeStopped"] = _partyManager.isTimeStopped();
    j["targetSelectorActive"] = _targetSelector.IsActive();

    auto dumpEntity = [](BattleEntity* e) {
        nlohmann::json ej;
        ej["name"] = e->name;
        ej["hp"] = e->hp;
        ej["maxHp"] = e->maxHp;
        ej["alive"] = e->Alive();
        ej["selected"] = e->selected;
        ej["isEnemy"] = e->isEnemy;
        return ej;
    };

    j["players"] = nlohmann::json::array();
    for (size_t i = 0; i < 4; ++i)
        if (BattleEntity* e = _partyManager.GetPlayer(i))
            j["players"].push_back(dumpEntity(e));

    j["enemies"] = nlohmann::json::array();
    for (size_t i = 0; i < 4; ++i)
        if (BattleEntity* e = _partyManager.GetEnemy(i))
            j["enemies"].push_back(dumpEntity(e));

    return j.dump();
}

void BattleState::InitPlayerParty()
{
    for (size_t i = 0; i < 4; ++i)
    {
        BattleEntity* character = _partyManager.GetPlayer(i);

        if (!character) continue;

        TraceLog(LOG_INFO, "[PARTY] character: %s", character->name.c_str());
        character->getSprite().SetResource(&Game::GetResources().Get(character->name));
        character->getSprite().SetSize({88.0f, 128.0f});
        character->getSprite().SetRectSize({88.0f, 128.0f});

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

std::vector<BattleEntity*> BattleState::GatherAllTargets()
{
    std::vector<BattleEntity*> result;
    result.reserve(8);
 
    for (size_t i = 0; i < 4; ++i)
    {
        if (BattleEntity* e = _partyManager.GetPlayer(i))
            result.push_back(e);
    }
    for (size_t i = 0; i < 4; ++i)
    {
        if (BattleEntity* e = _partyManager.GetEnemy(i))
            result.push_back(e);
    }

    return result;
}

#ifdef PLATFORM_WEB
#include <emscripten/emscripten.h>

namespace {
    std::string g_lastBattleStateDump;
}

extern "C" {
    EMSCRIPTEN_KEEPALIVE const char* TestApi_GetBattleState() {
        g_lastBattleStateDump = BattleState::s_active ? BattleState::s_active->DumpTestState() : "null";
        return g_lastBattleStateDump.c_str();
    }
}
#endif
