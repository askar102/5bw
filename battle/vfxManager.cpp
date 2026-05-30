/**
 * @file vfxManager.cpp
 * @author askar102
 * @brief Vfx spawner
 * @date 2026-05-07
 * 
 * @copyright Copyright (c) 2026, askar102
 * 
 */

#include "vfxManager.h"

void VfxManager::Update(float dt)
{
    for (auto it = _effects.begin(); it != _effects.end(); )
    {
        (*it)->Update(dt);

        if ((*it)->IsFinished())
        {
            it = _effects.erase(it);
        }
        else
        {
            ++it;
        }
    }

    for (auto& b : _bullets)
        b->Update(dt);

    _bullets.erase(
        std::remove_if(_bullets.begin(), _bullets.end(),
        [](const std::unique_ptr<BulletEntity>& b)
            {
                return b->IsFinished(); 
            }), 
        _bullets.end()
);
}

void VfxManager::Draw() const
{
    for (const auto& effect : _effects)
    {
        effect->Draw();
    }

    for (const auto& b : _bullets)
    {
        b->Draw();
    }
}
        

void VfxManager::Add(std::unique_ptr<Vfx> vfx)
{
    if (!vfx)
    {
        return;
    }

    vfx->OnEnter();
    _effects.push_back(std::move(vfx));
}

void VfxManager::Clear()
{
    _effects.clear();
    _bullets.clear();
}

void VfxManager::SpawnCardVfx(Vector2 position,
                              float lifetime,
                              float rotation,
                              AbilityType bulletType,
                              int abilityDamage,
                              PartyManager* partyManager,
                              DamageableSide damageSide,
                              bool peaceful,
                              bool animated)
{
    Add(std::make_unique<CardVfx>(
        position,
        lifetime,
        rotation,
        &Game::GetResources().Get(TextureID::CardVFX),
        bulletType,
        abilityDamage,
        partyManager,
        damageSide,
        peaceful,
        animated));
}

void VfxManager::SpawnDefendVfx(Vector2 origin, Vector2 target)
{
    (void)origin;
    (void)target;
}

void VfxManager::SpawnHealVfx(Vector2 origin, Vector2 target)
{
    (void)origin;
    (void)target;
}

void VfxManager::AddBullet(std::unique_ptr<BulletEntity> bullet)
{
    if (!bullet) return;
    _bullets.push_back(std::move(bullet));
}

BulletEntity* VfxManager::SpawnBullet(TextureResource* texture,
                                       Vector2          position,
                                       float            rotation,
                                       float            speed,
                                       float            lifetime,
                                       AbilityType      bulletType,
                                       DamageableSide   damageSide,
                                       PartyManager*    pm,
                                       bool             peaceful)
{
    auto bullet = std::make_unique<BulletEntity>(
        texture, position, rotation, speed, lifetime,
        bulletType, damageSide, peaceful
    );
    bullet->SetPartyManager(pm);

    BulletEntity* raw = bullet.get();
    _bullets.push_back(std::move(bullet));
    return raw;
}