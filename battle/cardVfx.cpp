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
                 TextureResource *textureResource,
                 AbilityType bulletType, int abilityDamage,
                 PartyManager *partyManager, DamageableSide damageSide,
                 bool peaceful, bool animated)
    : Vfx(position, lifetime, rotation, textureResource, WHITE),
      _partyManager(partyManager),
      _bulletType(bulletType),
      _abilityDamage(abilityDamage),
      _damageSide(damageSide),
      _peaceful(peaceful),
      _animated(animated) {}

void CardVfx::OnEnter() 
{ 
    SetSpeed(400.0f); 
    _sprite.SetSize({50, 50});
}

BattleEntity* CardVfx::GetUnitInDamageSide(size_t index) const
{
    if (!_partyManager)
        return nullptr;

    return _damageSide == DamageableSide::Enemy
        ? _partyManager->GetEnemy(index)
        : _partyManager->GetPlayer(index);
}

bool CardVfx::IsBulletAttack() const
{
    return _bulletType == AbilityType::BulletDefault ||
           _bulletType == AbilityType::BulletSplash;
}

void CardVfx::ApplyHit(BattleEntity& unit, int damage)
{
    if (damage <= 0 || !unit.Alive())
        return;

    if (IsBulletAttack())
        unit.EnemyHitAnimation();

    unit.Damage(damage);
}

void CardVfx::ApplySplashHitDamage()
{
    if (_peaceful || _abilityDamage <= 0 || !_partyManager)
        return;

    const int perUnit = _abilityDamage / PARTY_SLOT_COUNT;
    if (perUnit <= 0)
        return;

    const Rectangle projectileRect = _sprite.GetRect();

    for (size_t i = 0; i < PARTY_SLOT_COUNT; ++i)
    {
        BattleEntity* unit = GetUnitInDamageSide(i);
        if (!unit || !unit->Alive() || _touchedUnits.contains(unit))
            continue;

        if (!CheckCollisionRecs(projectileRect, unit->getSprite().GetRect()))
            continue;

        _touchedUnits.insert(unit);
        ApplyHit(*unit, perUnit);
    }
}

void CardVfx::ApplyDefaultHitDamage()
{
    if (_peaceful || _abilityDamage <= 0 || !_partyManager || _hitTarget)
        return;

    const int perUnit = _abilityDamage / CARD_ATTACK_PROJECTILE_COUNT;
    if (perUnit <= 0)
        return;

    const Rectangle projectileRect = _sprite.GetRect();

    for (size_t i = 0; i < PARTY_SLOT_COUNT; ++i)
    {
        BattleEntity* unit = GetUnitInDamageSide(i);
        if (!unit || !unit->Alive())
            continue;

        if (!CheckCollisionRecs(projectileRect, unit->getSprite().GetRect()))
            continue;

        ApplyHit(*unit, perUnit);
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
        for (size_t i = 0; i < PARTY_SLOT_COUNT; ++i)
        {
            BattleEntity* unit = GetUnitInDamageSide(i);
            if (!unit || !unit->Alive())
                continue;

            if (_bulletType == AbilityType::BulletSplash && _touchedUnits.contains(unit))
                continue;

            if (CheckCollisionRecs(projectileRect, unit->getSprite().GetRect()))
                return true;
        }

        return false;
    }

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
    if (projectileRect.x > Game::GetVirtualPos().x ||
        projectileRect.x + projectileRect.width < 0 ||
        projectileRect.y > Game::GetVirtualPos().y ||
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
