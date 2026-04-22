#pragma once

#include "battleEntity.h"

#include <array>
#include <memory>

class Party {
private:
    std::array<std::unique_ptr<BattleEntity>, 4> characters;
    
public:
    void Add(std::unique_ptr<BattleEntity> character, size_t index);
    void Remove(size_t index);
    
    void Clear();
    
    BattleEntity* Get(size_t index);
};