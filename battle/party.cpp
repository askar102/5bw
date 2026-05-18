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

void Party::Init()
{
    std::array<std::string, 4> configParty = ConfigReader::GetPlayerPartyFromConfig();

    for (size_t i = 0; i < configParty.size(); ++i)
    {
        std::string str = configParty[i];

        if (!str.empty())
        {
            auto character = std::make_unique<BattleEntity>(ConfigReader::GetCharacterFromConfig(str));

            character->getSprite().SetPosition(this->GetPositionByIndex(i));

            Add(std::move(character), i);
        }
    }

}

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

BattleEntity* Party::Get(size_t index) 
{
    if (index >= 4) return nullptr;
    return characters[index].get();
}

Vector2 Party::GetPositionByIndex(size_t index)
{
    switch (index) {
        case 0: return {200, 480};
        case 1: return {180, 350};
        case 2: return {90, 490};
        case 3: return {85, 450};
    };
}