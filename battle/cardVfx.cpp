/**
 * @file cardVfx.cpp
 * @author askar102
 * @brief Card bullet vfx
 * @date 2026-05-07
 *
 * @copyright Copyright (c) 2026, askar102
 *
 */

#include "cardVfx.h"

#include "ability.h"
#include "partyManager.h"

CardVfx::CardVfx(Vector2 position, float lifetime, float rotation,
                 TextureResource *textureResource, BattleEntity &target,
                 AbilityType bulletType, int abilityDamage,
                 PartyManager *partyManager, bool peaceful, bool animated)
    : Vfx(position, lifetime, rotation, textureResource, WHITE),
      _target(&target),
      _partyManager(partyManager),
      _bulletType(bulletType),
      _abilityDamage(abilityDamage),
      _peaceful(peaceful),
      _animated(animated) {}

void CardVfx::OnEnter() 
{ 
    SetSpeed(400.0f); 
    _sprite.SetSize({50, 50});
}

void CardVfx::ApplySplashHitDamage()
{
    if (_peaceful || _abilityDamage <= 0 || !_partyManager)
        return;

    const int perEnemy = _abilityDamage / SPLASH_ENEMY_COUNT;
    if (perEnemy <= 0)
        return;

    const Rectangle projectileRect = _sprite.GetRect();

    for (size_t i = 0; i < SPLASH_ENEMY_COUNT; ++i)
    {
        BattleEntity* enemy = _partyManager->GetEnemy(i);
        if (!enemy || _touchedEnemies.contains(enemy))
            continue;

        if (!CheckCollisionRecs(projectileRect, enemy->getSprite().GetRect()))
            continue;

        _touchedEnemies.insert(enemy);
        enemy->EnemyHitAnimation();
        enemy->Damage(perEnemy);
    }
}

void CardVfx::ApplyDefaultHitDamage()
{
    if (_peaceful || _abilityDamage <= 0 || !_partyManager || _hitTarget)
        return;

    const int perTarget = _abilityDamage / CARD_ATTACK_PROJECTILE_COUNT;
    if (perTarget <= 0)
        return;

    const Rectangle projectileRect = _sprite.GetRect();

    for (size_t i = 0; i < SPLASH_ENEMY_COUNT; ++i)
    {
        BattleEntity* enemy = _partyManager->GetEnemy(i);
        if (!enemy)
            continue;

        if (!CheckCollisionRecs(projectileRect, enemy->getSprite().GetRect()))
            continue;

        enemy->EnemyHitAnimation();
        enemy->Damage(perTarget);
        _hitTarget = true;
        return;
    }
}

bool CardVfx::CheckHitCollision() const
{
    const Rectangle projectileRect = _sprite.GetRect();

    if (_partyManager &&
        (_bulletType == AbilityType::BulletSplash ||
         _bulletType == AbilityType::BulletDefault))
    {
        for (size_t i = 0; i < SPLASH_ENEMY_COUNT; ++i)
        {
            BattleEntity* enemy = _partyManager->GetEnemy(i);
            if (!enemy)
                continue;

            if (_bulletType == AbilityType::BulletSplash && _touchedEnemies.contains(enemy))
                continue;

            if (CheckCollisionRecs(projectileRect, enemy->getSprite().GetRect()))
                return true;
        }

        return false;
    }

    if (_target)
        return CheckCollisionRecs(projectileRect, _target->getSprite().GetRect());

    return false;
}

void CardVfx::Update(float dt) {
  if (_animated) {
    const Vector2 position = _sprite.GetPosition();

    float rad = _sprite.GetRotation() * DEG2RAD;

    Vector2 direction = {std::cos(rad), std::sin(rad)};

    Vector2 nextPosition = {position.x + direction.x * _speed * dt,
                            position.y + direction.y * _speed * dt};

    _sprite.SetPosition(nextPosition);

    if (_bulletType == AbilityType::BulletDefault)
    {
      ApplyDefaultHitDamage();
    }
    else if (_bulletType == AbilityType::BulletSplash)
    {
      ApplySplashHitDamage();
    }

    const Rectangle projectileRect = _sprite.GetRect();
    if (projectileRect.x > static_cast<float>(GetScreenWidth()) ||
        projectileRect.x + projectileRect.width < 0 ||
        projectileRect.y > static_cast<float>(GetScreenHeight()) ||
        projectileRect.y + projectileRect.height < 0) {
      _leftScreen = true;
    }
  }

  Vfx::Update(dt);
}

void CardVfx::Draw() {
  float t = _elapsed / _lifetime;
  float alpha = 1.0f - t;

  _sprite.SetAlpha(alpha);
  _sprite.Draw();
}

bool CardVfx::IsFinished() const {
  return _hitTarget || _leftScreen || Vfx::IsFinished();
}

bool CardVfx::Hitted()
{
    return _hitTarget;
}
