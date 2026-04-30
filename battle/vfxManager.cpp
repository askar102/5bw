#include "vfxManager.h"

#include "battleEntity.h"
#include "battleResources.h"
#include "cardVfx.h"

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
}

void VfxManager::Draw() const
{
    for (const auto& effect : _effects)
    {
        effect->Draw();
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
}


void VfxManager::InitTextureManager(BattleResources* resources)
{
    _resources = resources;
}

void VfxManager::SpawnCardVfx(Vector2 position, float lifetime, float rotation, BattleEntity& target, bool peaceful, bool animated)
{
    if (!_resources)
    {
        return;
    }

    Add(std::make_unique<CardVfx>(position, lifetime, rotation, _resources->CardVFXTexture(), target, peaceful, animated));
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
