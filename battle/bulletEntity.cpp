/**
 * @file bulletEntity.cpp
 * @author askar102
 * @brief A projectile that is a full BattleEntity (eto pizda)
 * @date 2026-05-30
 *
 * @copyright Copyright (c) 2026, askar102
 *
 */

 #include "bulletEntity.h"
 #include "partyManager.h"
 
 
 BulletEntity::BulletEntity(TextureResource*  textureResource,
                            Vector2           position,
                            float             rotation,
                            float             speed,
                            float             lifetime,
                            AbilityType       bulletType,
                            DamageableSide    damageSide,
                            bool              peaceful)
     : BattleEntity() 
     , _speed(speed)
     , _lifetime(lifetime)
     , _bulletType(bulletType)
     , _damageSide(damageSide)
     , _peaceful(peaceful)
 {
     
     immortal = true;
 
     canSelected = false;
 
     getSprite().SetResource(textureResource);
     getSprite().SetPosition(position);

     getSprite().SetRotation(rotation);
 }
 
 void BulletEntity::SetOnTouched(std::function<void(BulletEntity&, BattleEntity&)> cb)
 {
     _onTouched = std::move(cb);
 }
 
 void BulletEntity::SetOnFinish(std::function<void(BulletEntity&)> cb)
 {
     _onFinish = std::move(cb);
 }
 
 void BulletEntity::SetSpeed(float speed)
 {
     _speed = speed;
 }
 
 void BulletEntity::SetLifetime(float lifetime)
 {
     _lifetime = lifetime;
 }
 
 void BulletEntity::SetPeaceful(bool peaceful)
 {
     _peaceful = peaceful;
 }
 
 void BulletEntity::SetSource(BattleEntity* source)
 {
     _source = source;
 }
 
 BattleEntity* BulletEntity::GetSource() const
 {
     return _source;
 }
 
 void BulletEntity::SetPartyManager(PartyManager* pm)
 {
     _pm = pm;
 }

 void BulletEntity::SetBulletType(AbilityType bulletType)
 {
    _bulletType = bulletType;
 }
 

 void BulletEntity::Update(float dt)
 {
     if (IsFinished()) return;

     BattleEntity::Update(dt);
 
     Vector2 pos = getSprite().GetPosition();
     float   rad = getSprite().GetRotation() * DEG2RAD;
 
     pos.x += std::cos(rad) * _speed * dt;
     pos.y += std::sin(rad) * _speed * dt;
     getSprite().SetPosition(pos);
    
     // lifetime
     if (_lifetime > 0.0f)
     {
         _elapsed += dt;
         if (_elapsed >= _lifetime)
         {
             Finish();
             return;
         }
     }
     
     // off-screen
     Rectangle r = getSprite().GetRect();
     if (r.x > static_cast<float>(GetScreenWidth())  ||
         r.x + r.width  < 0.0f                        ||
         r.y > static_cast<float>(GetScreenHeight())  ||
         r.y + r.height < 0.0f)
     {
         _leftScreen = true;
         Finish();
         return;
     }
 
     // collide
     if (!_peaceful || _onTouched)
         CheckCollisions();
 
     // self-destruct after hit
     if (_hitTarget)
         Finish();
 
     // sprite update
     getSprite().Update(dt);
 }
 

 void BulletEntity::Draw()
 {
     getSprite().Draw();
 }
 
 bool BulletEntity::IsFinished() const
 {
     return _hitTarget || _leftScreen || (_lifetime > 0.0f && _elapsed >= _lifetime);
 }
 

 BattleEntity* BulletEntity::GetEntityAt(size_t index) const
 {
     if (!_pm) return nullptr;
 
     return (_damageSide == DamageableSide::Enemy)
         ? _pm->GetEnemy(index)
         : _pm->GetPlayer(index);
 }
 
 void BulletEntity::CheckCollisions()
 {
     if (!_pm) return;
 
     const Rectangle bulletRect = getSprite().GetRect();
 
     for (size_t i = 0; i < PARTY_SLOT_COUNT; ++i)
     {
         BattleEntity* target = GetEntityAt(i);
         if (!target || !target->Alive()) continue;
 
         // splash logic
         if (_bulletType == AbilityType::BulletSplash && _touched.contains(target))
             continue;
 
         // default logic    
         if (_bulletType == AbilityType::BulletDefault && _hitTarget)
             break;
 
         if (!CheckCollisionRecs(bulletRect, target->getSprite().GetRect()))
             continue;
 
         // hit register
         _touched.insert(target);
 
         if (_onTouched)
             _onTouched(*this, *target);
 
         if (_bulletType == AbilityType::BulletDefault)
         {
             _hitTarget = true;
             break;
         }
     }
 }
 
 void BulletEntity::Finish()
 {
     _hitTarget  = (_bulletType == AbilityType::BulletDefault) ? _hitTarget  : _hitTarget;

     if (_lifetime > 0.0f) _elapsed = _lifetime;
     else                   _hitTarget = true; 
 
     if (_onFinish)
     {
         _onFinish(*this);
         _onFinish = nullptr;
     }
 }