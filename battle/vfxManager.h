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

    /**
    * @brief card vfx spawn
    * 
    * @param position postion of vfx
    * @param lifetime lifetime of vfx
    * @param rotation rotation of vfx
    * @param target target of vfx
    * @param peaceful will use EnemyHitAnimation or not? default value: true
    */
    void SpawnCardVfx(Vector2 position, float lifetime, float rotation, BattleEntity& target, bool peaceful = true);
    void SpawnDefendVfx(Vector2 origin, Vector2 target);
    void SpawnHealVfx(Vector2 origin, Vector2 target);

    void InitTextureManager(BattleResources* resources);

private:
    std::vector<std::unique_ptr<Vfx>> _effects;
    BattleResources* _resources = nullptr;
};
