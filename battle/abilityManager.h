#pragma once

#include "../raylib/raylib.h"

#include "battleEntity.h"
#include "battleResources.h"
#include "vfxManager.h"

#include <cmath>
#include <random>

namespace AbilityManager {
    namespace CardGuy {
        void SpawnCardAttack(BattleResources& resManager, VfxManager& vfxManager, BattleEntity& caster, BattleEntity& target, int damage);
        void SpawnCardHeal(BattleResources& resManager, VfxManager& vfxManager, BattleEntity& caster, BattleEntity& target);
        void SpawnCardBlock(VfxManager& vfxManager, BattleEntity& caster);
    }
}