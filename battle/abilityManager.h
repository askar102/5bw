#pragma once

#include "../raylib/raylib.h"

#include "battleEntity.h"
#include "battleResources.h"
#include "vfxManager.h"

namespace AbilityManager {
    namespace CardGuy {
        void SpawnCardAttack(BattleResources& resManager, VfxManager& vfxManager, BattleEntity& caster, BattleEntity& target);
        void SpawnCardHeal(VfxManager& vfxManager, BattleEntity& caster, BattleEntity& target);
        void SpawnCardBlock(VfxManager& vfxManager, BattleEntity& caster);
    }
}