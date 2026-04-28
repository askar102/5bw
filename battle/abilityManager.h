#pragma once

#include "../raylib/raylib.h"

#include "battleEntity.h"
#include "vfxManager.h"

namespace AbilityManager {
    namespace CardGuy {
        void SpawnCardAttack(VfxManager& vfxManager, BattleEntity& caster, BattleEntity& target);
        void SpawnCardHeal(VfxManager& vfxManager, BattleEntity& caster, BattleEntity& target);
        void SpawnCardBlock(VfxManager& vfxManager, BattleEntity& caster);
    }
}