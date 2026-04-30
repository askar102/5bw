#include "abilityManager.h"

namespace AbilityManager {
    namespace CardGuy {
        void SpawnCardAttack(BattleResources& resManager, VfxManager& vfxManager, BattleEntity& caster, BattleEntity& target, int damage)
        {
            Vector2 casterPos = caster.getSprite().getPosition();
            Vector2 cardPostion = {
                casterPos.x + 40,
                casterPos.y + (caster.getSprite().getSize().y / 2)
            };

            caster.getSprite().setTexture(resManager.CardGuyAtlasTexture());
            caster.getSprite().setCostume(1, 1.0f); // second costume from 3-part atlas

            // up
            vfxManager.SpawnCardVfx(cardPostion, 5.0f, -10.0f, target, false);

            // mid
            vfxManager.SpawnCardVfx(cardPostion, 5.0f, 0.0f, target, false);

            // down
            vfxManager.SpawnCardVfx(cardPostion, 5.0f, 10.0f, target, false);
        }

        void SpawnCardHeal(BattleResources& resManager, VfxManager& vfxManager, BattleEntity& caster, BattleEntity& target)
        {
            const int countOfClones = 25;

            // TODO: next.
            caster.getSprite().setTexture(resManager.CardGuyAtlasTexture());
            caster.getSprite().setCostume(2, 1.0f);

            Vector2 casterPos = caster.getSprite().getPosition();

            for (int i = 0; i < countOfClones; ++i)
            {
                float xOffset = (float)(GetRandomValue(0, 180));

                Vector2 cardPostion = {
                    casterPos.x + xOffset,
                    casterPos.y + 200
                };

                vfxManager.SpawnCardVfx(cardPostion, 1.0f, -90.0f, target, true);
            }
            
        }   

        void SpawnCardBlock(VfxManager& vfxManager, BattleEntity& caster)
        {
            (void)vfxManager;
            (void)caster;
        }

    } // namespace CardGuy
} // namespace AbilityManager