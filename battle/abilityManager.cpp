#include "abilityManager.h"

namespace AbilityManager {
namespace CardGuy {

void SpawnCardAttack(BattleResources& resManager, VfxManager& vfxManager, BattleEntity& caster, BattleEntity& target)
{
    const Rectangle targetRect = target.getSprite().getRect();

    Vector2 casterPos = caster.getSprite().getPosition();
    Vector2 cardPostion = {
        casterPos.x + 40,
        casterPos.y + (caster.getSprite().getSize().y / 2)
    };

    caster.getSprite().setTexture(resManager.CardAttackTexture());

    // up
    vfxManager.SpawnCardVfx(cardPostion, 5.0f, -10.0f, target);

    // mid
    vfxManager.SpawnCardVfx(cardPostion, 5.0f, 0.0f, target);

    // down
    vfxManager.SpawnCardVfx(cardPostion, 5.0f, 10.0f, target);
}

void SpawnCardHeal(VfxManager& vfxManager, BattleEntity& caster, BattleEntity& target)
{
    (void)vfxManager;
    (void)caster;
    (void)target;
}

void SpawnCardBlock(VfxManager& vfxManager, BattleEntity& caster)
{
    (void)vfxManager;
    (void)caster;
}

} // namespace CardGuy
} // namespace AbilityManager