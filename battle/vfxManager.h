/**
 * @file vfxManager.h
 * @author askar102
 * @brief Vfx spawner
 * @date 2026-05-07
 * 
 * @copyright Copyright (c) 2026, askar102
 * 
 */

#pragma once

#include <memory>
#include <vector>

#include "../raylib/raylib.h"
#include "../core/game.h"

#include "vfx.h"
#include "battleEntity.h"
#include "ability.h"
#include "battleSide.h"
#include "cardVfx.h"

class BattleEntity;
class PartyManager;

class VfxManager {
public:
    void Update(float dt);
    void Draw() const;

    void Add(std::unique_ptr<Vfx> vfx);
    void Clear();

    void SpawnCardVfx(Vector2 position,
                      float lifetime,
                      float rotation,
                      AbilityType bulletType,
                      int abilityDamage,
                      PartyManager* partyManager,
                      DamageableSide damageSide,
                      bool peaceful = true,
                      bool animated = true);
    void SpawnDefendVfx(Vector2 origin, Vector2 target);
    void SpawnHealVfx(Vector2 origin, Vector2 target);

private:
    std::vector<std::unique_ptr<Vfx>> _effects;
};
