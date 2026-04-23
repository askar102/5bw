#pragma once

#include <string>

class BattleEntity;

class Ability {
private:
    std::string _name;
    int _damage = 0;
    int _heal = 0;

public:
    Ability() = default;
    Ability(const std::string& abilityName, int abilityDamage = 0, int abilityHeal = 0);

    virtual ~Ability() = default;

    virtual void Execute(BattleEntity& caster, BattleEntity& target);

    std::string getName() const;
};