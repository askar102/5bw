/**
 * @file ability.h
 * @author askar102
 * @brief Ability type
 * @date 2026-05-03
 * 
 * @copyright Copyright (c) 2026, askar102
 * 
 */

#pragma once

#include <string>

#include "BattleEntity.h"

class BattleEntity;

class Ability {
public:
    Ability() = default;
    Ability(const std::string& abilityName, int abilityDamage = 0, int abilityHeal = 0);

    virtual ~Ability() = default;

    virtual void Execute(BattleEntity& caster, BattleEntity& target, bool skipDamageAction = false);

    std::string GetName() const;
    int GetDamage() const;
    int GetHeal() const;

private:
    std::string _name;
    int _damage = 0;
    int _heal = 0;
};