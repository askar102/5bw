#include "vfxManager.h"

#include <algorithm>

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

void VfxManager::SpawnAttackVfx(Vector2 origin, Vector2 target)
{
    (void)origin;
    (void)target;
    // TODO: add attack card spread VFX here.
}

void VfxManager::SpawnDefendVfx(Vector2 origin, Vector2 target)
{
    (void)origin;
    (void)target;
    // TODO: add defend shield VFX here.
}

void VfxManager::SpawnHealVfx(Vector2 origin, Vector2 target)
{
    (void)origin;
    (void)target;
    // TODO: add heal sparkle VFX here.
}
