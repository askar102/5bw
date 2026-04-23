#include "vfxManager.h"

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


void VfxManager::SpawnCardVfx()
{
    if (!_resources)
    {
        return;
    }

    Add(std::make_unique<CardVfx>(Vector2{0, 0}, 10.0f, _resources->CardVFXTexture()));
}

void VfxManager::SpawnDefendVfx(Vector2 origin, Vector2 target)
{
    (void)origin;
    (void)target;
    // TODO: сюда добавить VFX защиты.
}

void VfxManager::SpawnHealVfx(Vector2 origin, Vector2 target)
{
    (void)origin;
    (void)target;
    // TODO: сюда добавить VFX лечения.
}
