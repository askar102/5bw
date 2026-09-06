#ifndef EVENTS_H
#define EVENTS_H

// Forward declaratio for pointers
class Ability;
class VfxManager;
class BattleEntity;
class PartyManager;
class StateManager;

// ------------- COMMANDS --------------
struct UseAbilityCommand
{
    Ability* clickedAbility;
    VfxManager* vfxManager;
    BattleEntity* caster;
    BattleEntity* target;
    PartyManager* partyManager;
    StateManager* stateManager;
};


// ------------- EVENTS ----------------
struct UsedAbilityEvent
{
    Ability* ability;
    BattleEntity* caster;
    BattleEntity* target;
};


#endif