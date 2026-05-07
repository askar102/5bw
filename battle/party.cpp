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

void Party::Add(std::unique_ptr<BattleEntity> character, size_t index) 
{
    if (index >= 4) return;

    characters[index] = std::move(character);
}

void Party::Remove(size_t index)
{
    if (index >= 4) return;

    characters[index].reset();
}

void Party::Clear() 
{
    for (auto& c : characters) {
        c.reset();
    }
}

BattleEntity* Party::Get(size_t index) {
    if (index >= 4) return nullptr;
    return characters[index].get();
}
