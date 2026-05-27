/**
 * @file cardVfx.h
 * @author askar102
 * @brief Card bullet vfx
 * @date 2026-05-07
 * 
 * @copyright Copyright (c) 2026, askar102
 * 
 */

#pragma once

#include "ability.h"
#include "battleEntity.h"
#include "vfx.h"

class PartyManager;

class CardVfx : public Vfx {
public:
    CardVfx(Vector2 position, 
            float lifetime, 
            float rotation, 
            TextureResource* textureResource, 
            BattleEntity& target,
            AbilityType bulletType,
            int abilityDamage,
            PartyManager* partyManager,
            bool peaceful = true, 
            bool animated = true);

    void OnEnter() override;
    void Update(float dt) override;
    void Draw() override;
    bool IsFinished() const override;

    bool Hitted();

private:
    void ApplyHitDamage();
    bool CheckHitCollision() const;

    BattleEntity* _target;
    PartyManager* _partyManager = nullptr;
    AbilityType _bulletType = AbilityType::BulletDefault;
    int _abilityDamage = 0;
    bool _leftScreen = false;
    bool _peaceful = true;
    bool _animated = true;

    static constexpr int SPLASH_ENEMY_COUNT = 4;
    static constexpr int CARD_ATTACK_PROJECTILE_COUNT = 3;
};
    
