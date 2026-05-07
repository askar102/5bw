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

#include "../raylib/raylib.h"

#include "../core/game.h"

#include "battleEntity.h"
#include "vfxManager.h"


namespace AbilityManager {
    namespace CardGuy {
        void SpawnCardAttack(VfxManager& vfxManager, BattleEntity& caster, BattleEntity& target, int damage);
        void SpawnCardHeal(VfxManager& vfxManager, BattleEntity& caster, BattleEntity& target);
        void SpawnCardBlock(VfxManager& vfxManager, BattleEntity& caster, BattleEntity& target);
    }
}