#include "battleSystem.h"

void BattleSystem::UseAbility(BattleEntity& caster, BattleEntity& target, Ability* ability)
{
    if (!ability) return;

    ability->Execute(caster, target);
}