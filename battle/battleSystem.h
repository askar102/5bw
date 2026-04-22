#pragma once

#include "ability.h"
#include "battleEntity.h"

class BattleSystem {
public:
    void UseAbility(BattleEntity& caster,
                    BattleEntity& target,
                    Ability* ability);
};