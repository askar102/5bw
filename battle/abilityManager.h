/**
 * @file abilityManager.h
 * @author askar102
 * @brief Directly calling characters' abilities
 * @date 2026-05-07
 * 
 * @copyright Copyright (c) 2026, askar102
 * 
 */

#pragma once

#include <cmath>
#include <random>
#include <string>
#include <vector>
#include <set>

#include "../raylib/raylib.h"

#include "../core/game.h"
#include "../states/sceneState.h"

#include "battleEntity.h"
#include "partyManager.h"
#include "vfxManager.h"

#include "targetSelector.h"

#include "../gui/button.h"


namespace AbilityManager {
    void SpawnAbility(Ability& clickedAbility,
                      VfxManager& vfxManager,
                      BattleEntity& caster,
                      BattleEntity& target,
                      PartyManager& partyManager,
                      StateManager* stateManager);

    TargetAbilityDesc MakeTargetDesc(Ability& ability,
                        VfxManager& vfxManager,
                        PartyManager& partyManager,
                        StateManager* stateManager);


    namespace CardGuy {
        void SpawnCardAttack(VfxManager& vfxManager,
                             BattleEntity& caster,
                             BattleEntity& target,
                             const Ability& ability,
                             PartyManager& partyManager);
        void SpawnCardHeal(VfxManager& vfxManager, BattleEntity& caster, BattleEntity& target, const Ability& ability,  PartyManager& partyManager);
        void SpawnCardBlock(VfxManager& vfxManager, BattleEntity& caster, BattleEntity& target, PartyManager& partyManager);

        void SpawnCardChoose(VfxManager& vfxManager, BattleEntity& caster, BattleEntity& target, PartyManager& partyManager);
    }

    namespace AngryGuy {
        void SpawnSpeedDash(VfxManager& vfxManager, BattleEntity& caster, BattleEntity& target, const Ability& ability, PartyManager& partyManager);
        void SpawnSpeedSpin(VfxManager& vfxManager, BattleEntity& caster, BattleEntity& target, const Ability& ability, PartyManager& partyManager);
        void SpawnScream(VfxManager& vfxManager, BattleEntity& caster, BattleEntity& target, const Ability& ability, PartyManager& partyManager, StateManager* stateManager);
    }

    namespace SigmaMen {
        void SpawnPencilThrow(VfxManager& vfxManager, BattleEntity& caster, BattleEntity& target, const Ability& ability, PartyManager& partyManager);
        void SpawnPenThrow(VfxManager& vfxManager, BattleEntity& caster, BattleEntity& target, const Ability& ability, PartyManager& partyManager);
        void SpawnTimestop(VfxManager& vfxManager, BattleEntity& caster, BattleEntity& target, const Ability& ability, PartyManager& partyManager);
    }

    // Enemies
    namespace ForestEnemies {
        void SpawnEnemyDash(VfxManager& vfxManager, BattleEntity& caster, BattleEntity& target, const Ability& ability, PartyManager& partyManager);
    }
}   
