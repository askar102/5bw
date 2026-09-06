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
#include <unordered_map>
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

#include <functional>
#include <unordered_map>

namespace AbilityManager {
    using AbilityHandler = std::function<void(VfxManager&, BattleEntity&, BattleEntity&, const Ability&, PartyManager&, StateManager*)>;
    inline std::unordered_map<std::string, AbilityHandler> g_abilities;

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

    void InitAbilities();

    namespace CardGuy {
        void SpawnCardAttack(VfxManager& vfxManager,
                             BattleEntity& caster,
                             BattleEntity& target,
                             const Ability& ability,
                             PartyManager& partyManager,
                             StateManager* stateManager);
        void SpawnCardHeal(VfxManager& vfxManager, BattleEntity& caster, BattleEntity& target, const Ability& ability, PartyManager& partyManager, StateManager* stateManager);
        void SpawnCardBlock(VfxManager& vfxManager, BattleEntity& caster, BattleEntity& target, const Ability& ability, PartyManager& partyManager, StateManager* stateManager);

        void SpawnCardChoose(VfxManager& vfxManager, BattleEntity& caster, BattleEntity& target, const Ability& ability, PartyManager& partyManager, StateManager* stateManager);
    }

    namespace AngryGuy {
        void SpawnSpeedDash(VfxManager& vfxManager, BattleEntity& caster, BattleEntity& target, const Ability& ability, PartyManager& partyManager, StateManager* stateManager);
        void SpawnSpeedSpin(VfxManager& vfxManager, BattleEntity& caster, BattleEntity& target, const Ability& ability, PartyManager& partyManager, StateManager* stateManager);
        void SpawnScream(VfxManager& vfxManager, BattleEntity& caster, BattleEntity& target, const Ability& ability, PartyManager& partyManager, StateManager* stateManager);
    }

    namespace SigmaMen {
        void SpawnPencilThrow(VfxManager& vfxManager, BattleEntity& caster, BattleEntity& target, const Ability& ability, PartyManager& partyManager, StateManager* stateManager);
        void SpawnPenThrow(VfxManager& vfxManager, BattleEntity& caster, BattleEntity& target, const Ability& ability, PartyManager& partyManager, StateManager* stateManager);
        void SpawnTimestop(VfxManager& vfxManager, BattleEntity& caster, BattleEntity& target, const Ability& ability, PartyManager& partyManager, StateManager* stateManager);
    }

    // Enemies
    namespace ForestEnemies {
        void SpawnEnemyDash(VfxManager& vfxManager, BattleEntity& caster, BattleEntity& target, const Ability& ability, PartyManager& partyManager, StateManager* stateManager);
    }
}   
