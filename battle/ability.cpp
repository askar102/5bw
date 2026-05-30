/**
 * @file ability.cpp
 * @author askar102
 * @brief Ability type
 * @date 2026-05-03
 * 
 * @copyright Copyright (c) 2026, askar102
 * 
 */

#include "ability.h"

Ability::Ability(const std::string& abilityName, int abilityDamage, int abilityHeal, AbilityType abilityType)
    : _name(abilityName), _damage(abilityDamage), _heal(abilityHeal), _type(abilityType) {}

void Ability::Execute(BattleEntity& caster, BattleEntity& target, bool skipDamageAction, bool skipHealAction)
{
    if (!skipDamageAction)
        caster.Heal(_heal);
    if (!skipDamageAction)
        target.Damage(_damage);

}

std::string Ability::GetName() const
{
    return _name;
}

AbilityType Ability::GetType() const
{
    return _type;
}

int Ability::GetDamage() const
{
    return _damage;
}

int Ability::GetHeal() const
{
    return _heal;
}