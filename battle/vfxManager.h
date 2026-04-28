#pragma once

#include "vfx.h"
#include "battleResources.h"

#include "../raylib/raylib.h"

#include <memory>
#include <vector>

class BattleEntity;

class VfxManager {
public:
    void Update(float dt);
    void Draw() const;

    void Add(std::unique_ptr<Vfx> vfx);
    void Clear();

    // Temporary per-ability hooks. Keep these empty for now.
    void SpawnCardVfx(Vector2 casterPos, float casterHeight, BattleEntity& target);
    void SpawnDefendVfx(Vector2 origin, Vector2 target);
    void SpawnHealVfx(Vector2 origin, Vector2 target);

    void InitTextureManager(BattleResources* resources);

private:
    std::vector<std::unique_ptr<Vfx>> _effects;
    BattleResources* _resources = nullptr;
};
