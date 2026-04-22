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
