#pragma once

#include <string>

class BattleEntity;

class Ability {
public:
    std::string name;
    
    int damage = 0;
    int heal = 0;

    Ability() = default;
    Ability(const std::string& abilityName, int abilityDamage = 0, int abilityHeal = 0)
        : name(abilityName), damage(abilityDamage), heal(abilityHeal) {}
    virtual ~Ability() = default;
    
    virtual void Execute(BattleEntity& caster,
                         BattleEntity& target)
    {
        
    }
};