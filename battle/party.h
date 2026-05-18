/**
 * @file party.h
 * @author askar102
 * @brief The party system
 * @date 2026-05-07
 * 
 * @copyright Copyright (c) 2026, askar102
 * 
 */

#pragma once

#include <array>
#include <memory>

#include "battleEntity.h"

#include "../core/game.h"

#include "../misc/configReader.h"

class Party {
public:
    Party() 
    {
        Init();
    }

    void Init();

    void Add(std::unique_ptr<BattleEntity> character, size_t index);
    void Remove(size_t index);
    
    void Clear();
    
    BattleEntity* Get(size_t index);

private:
    std::array<std::unique_ptr<BattleEntity>, 4> characters;
};