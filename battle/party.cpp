/**
 * @file party.cpp
 * @author askar102
 * @brief The party system
 * @date 2026-05-07
 * 
 * @copyright Copyright (c) 2026, askar102
 * 
 */

#include "party.h"

#include "../core/game.h"

void Party::Init()
{}

void Party::Add(std::unique_ptr<BattleEntity> character, size_t index) 
{
    if (index >= characters.size()) return;

    characters[index] = std::move(character);
}

void Party::Remove(size_t index)
{
    if (index >= characters.size()) return;

    characters[index].reset();
}

void Party::Clear() 
{
    for (auto& c : characters) {
        c.reset();
    }
}

BattleEntity* Party::Get(size_t index) 
{
    if (index >= characters.size()) return nullptr;
    return characters[index].get();
}

Vector2 Party::GetPositionByIndex(size_t index)
{
    switch (index) {
        case 0: return {70, 280}; // верхний угол слева
        case 1: return {60, 380}; // нижний угол слева
        case 2: return {180, 280}; // верхний угол справа
        case 3: return {170, 380}; // нижний угол справа
        default: return {0, 0};
    };
}

BattleEntity* Party::GetSelectedCharacter()
{
    for (auto& character : characters)
    {
        if (character && character->selected)
        {
            return character.get();
        }
    }

    return nullptr;
}

void Party::DeselectAll()
{
    TraceLog(LOG_INFO, "[PARTY] DESELECT ALL");
    for (auto& character : characters)
    {
        if (character)
        {
            character->selected = false;
        }
    }
}

void Party::UpdateSelection()
{
    Vector2 mouse = Game::GetWorldMouse();

    for (auto& character : characters)
    {
        if (!character)
            continue;

        if (!character->canSelected)
            continue;

        if (CheckCollisionPointRec(mouse, character->getSprite().GetRect()))
        {

            if (!character->selected)
            {
                TraceLog(LOG_INFO, "[PARTY] SELECT %s", character->name.c_str());

                DeselectAll();
                character->selected = true;
            }

            return;
        }
    }

    // DeselectAll();
}


// effects
void Party::DamageAll(int amount, BattleEntity* source)
{
    for (auto& c : characters)
    {
        if (!c || !c->Alive()) continue;
        c->Damage(amount, source);
    }
}

void Party::HealAll(int amount)
{
    for (auto& c : characters)
    {
        if (!c || !c->Alive()) continue;
        c->Heal(amount);
    }
}

void Party::SetWeaknessEffectAll(int amount, float duration, std::function<void()> onDone, bool showUi)
{
    for (auto& c : characters)
    {
        if (!c || !c->Alive()) continue;
        c->SetWeaknessEffect(amount, duration, onDone, showUi);
    }
}

void Party::SetScreamEffectAll(float duration, std::function<void()> onDone, bool showUi)
{
    for (auto& c : characters)
    {
        if (!c || !c->Alive()) continue;
        c->SetScreamEffect(duration, onDone, showUi);
    }
}

void Party::SetStunEffectAll(float duration, std::function<void()> onDone, bool showUi)
{
    for (auto& c : characters)
    {
        if (!c || !c->Alive()) continue;
        c->SetStunEffect(duration, onDone, showUi);
    }
}
void Party::SetTimestopEffectAll(float duration, std::function<void()> onDone, bool showUi)
{
    for (auto& c : characters)
    {
        if (!c || !c->Alive()) continue;
        c->SetTimestopEffect(duration, onDone, showUi);
    }
}