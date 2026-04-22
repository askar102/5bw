#pragma once

#include "battleEntity.h"

#include <string>

class BattleEntity;

class Ability {
public:
    std::string name;
    
    int damage;
    int heal;
    
    std::string iconPath;
    
    virtual void Execute(BattleEntity& caster,
                            BattleEntity& target) = 0;
};