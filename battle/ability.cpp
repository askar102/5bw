#include "ability.h"
#include "BattleEntity.h"

Ability::Ability(const std::string& abilityName, int abilityDamage, int abilityHeal)
    : _name(abilityName), _damage(abilityDamage), _heal(abilityHeal) {}

void Ability::Execute(BattleEntity& caster, BattleEntity& target)
{
    caster.Heal(_heal);
    target.Damage(_damage);
}

std::string Ability::getName() const
{
    return _name;
}