#ifndef EVENTS_H
#define EVENTS_H

#include "vfxManager.h"
#include "battleEntity.h"
#include "partyManager.h"
#include "core/stateManager.h"
#include "abilityManager.h"

struct UseAbilityCommand
{
    Ability* clickedAbility;
    VfxManager* vfxManager;
    BattleEntity* caster;
    BattleEntity* target;
    PartyManager* partyManager;
    StateManager* stateManager;
};



#endif