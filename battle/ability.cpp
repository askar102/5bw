#include "ability.h"
#include "BattleEntity.h"

Ability::Ability(const std::string& abilityName, int abilityDamage, int abilityHeal)
    : _name(abilityName), _damage(abilityDamage), _heal(abilityHeal) {}

void Ability::Execute(BattleEntity& caster, BattleEntity& target, bool skipDamageAction)
{
    caster.Heal(_heal);
    if (!skipDamageAction)
        target.Damage(_damage);
}

std::string Ability::getName() const
{
    return _name;
}

int Ability::getDamage() const
{
    return _damage;
}

int Ability::getHeal() const
{
    return _heal;
}