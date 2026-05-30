/**
 * @file bulletEntity.h
 * @author askar102
 * @brief A projectile that is a full BattleEntity — has a sprite, hitbox,
 *        supports bullet_default / bullet_splash collision modes,
 *        fires callbacks on touch and on finish.
 * @date 2026-05-30
 *
 * @copyright Copyright (c) 2026, askar102
 *
 */

 #pragma once

 #include <functional>
 #include <unordered_set>
 
 #include "../raylib/raylib.h"
 
 #include "battleEntity.h"
 #include "ability.h"
 #include "battleSide.h"
 
 class PartyManager;
 
 class BulletEntity : public BattleEntity {
 public:
     BulletEntity(TextureResource*  textureResource,
                  Vector2           position,
                  float             rotation,
                  float             speed,
                  float             lifetime,
                  AbilityType       bulletType,
                  DamageableSide    damageSide,
                  bool              peaceful = false);
 

     void SetOnTouched(std::function<void(BulletEntity& bullet, BattleEntity& touched)> cb);

     void SetOnFinish(std::function<void(BulletEntity& bullet)> cb);

     void SetSpeed(float speed);
     void SetLifetime(float lifetime);
     void SetPeaceful(bool peaceful);

     void SetBulletType(AbilityType bulletType);

     void SetSource(BattleEntity* source);
     BattleEntity* GetSource() const;
 
     void Update(float dt);

     void Draw();

 
     bool IsFinished() const;
 

     void SetPartyManager(PartyManager* pm);
 
 private:
     float _speed = 400.0f;
 
     float _lifetime = 5.0f;
     float _elapsed = 0.0f;

     AbilityType _bulletType = AbilityType::BulletDefault;
     DamageableSide _damageSide = DamageableSide::Enemy;
     bool _peaceful    = false;
     bool _hitTarget   = false;  
     bool _leftScreen  = false;
 
     std::unordered_set<BattleEntity*> _touched; 

     BattleEntity* _source = nullptr;
     PartyManager* _pm = nullptr;
 
     std::function<void(BulletEntity&, BattleEntity&)> _onTouched;
     std::function<void(BulletEntity&)> _onFinish;
 
     BattleEntity* GetEntityAt(size_t index) const; 
     void CheckCollisions();
     void Finish();
 
     static constexpr int PARTY_SLOT_COUNT = 4;
 };