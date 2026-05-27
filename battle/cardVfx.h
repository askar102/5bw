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
#include "battleSide.h"
#include "vfx.h"
#include <unordered_set>

class PartyManager;

class CardVfx : public Vfx {
public:
    CardVfx(Vector2 position, 
            float lifetime, 
            float rotation, 
            TextureResource* textureResource,
            AbilityType bulletType,
            int abilityDamage,
            PartyManager* partyManager,
            DamageableSide damageSide,
            bool peaceful = true, 
            bool animated = true);

    void OnEnter() override;
    void Update(float dt) override;
    void Draw() override;
    bool IsFinished() const override;

    bool Hitted();

private:
    BattleEntity* GetUnitInDamageSide(size_t index) const;
    void ApplyDefaultHitDamage();
    void ApplySplashHitDamage();
    bool CheckHitCollision() const;
    bool IsBulletAttack() const;
    void ApplyHit(BattleEntity& unit, int damage);

    PartyManager* _partyManager = nullptr;
    AbilityType _bulletType = AbilityType::BulletDefault;
    int _abilityDamage = 0;
    DamageableSide _damageSide = DamageableSide::Enemy;
    bool _leftScreen = false;
    bool _peaceful = true;
    bool _animated = true;

    std::unordered_set<BattleEntity*> _touchedUnits;

    static constexpr int PARTY_SLOT_COUNT = 4;
    static constexpr int CARD_ATTACK_PROJECTILE_COUNT = 3;
};
    