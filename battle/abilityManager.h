#pragma once

#include "../raylib/raylib.h"

#include "battleEntity.h"
#include "battleResources.h"
#include "vfxManager.h"

#include "../core/game.h"

#include <cmath>
#include <random>

namespace AbilityManager {
    namespace CardGuy {
        void SpawnCardAttack(VfxManager& vfxManager, BattleEntity& caster, BattleEntity& target, int damage);
        void SpawnCardHeal(VfxManager& vfxManager, BattleEntity& caster, BattleEntity& target);
        void SpawnCardBlock(VfxManager& vfxManager, BattleEntity& caster, BattleEntity& target);
    }
}