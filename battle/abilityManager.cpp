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
            const int countOfClones = 15;

            caster.getSprite().setTexture(resManager.CardGuyAtlasTexture());
            caster.getSprite().setCostume(2, 1.0f);

            Vector2 casterPos = caster.getSprite().getPosition();

            for (int i = 0; i < countOfClones; ++i)
            {
                float xOffset = (float)(GetRandomValue(-30, 220));
                float yOffset = (float)(GetRandomValue(120, 320));

                Vector2 cardPostion = {
                    casterPos.x + xOffset,
                    casterPos.y + yOffset
                };

                vfxManager.SpawnCardVfx(cardPostion, 1.0f, -90.0f, target, true);
            }
            
        }   

        void SpawnCardBlock(BattleResources& resManager, VfxManager& vfxManager, BattleEntity& caster, BattleEntity& target)
        {
            /**
             * TODO: bug, sprite dont change costume, fix later
             * 
             */
            caster.getSprite().setTexture(resManager.CardGuyAtlasTexture());
            caster.getSprite().setCostume(2, 1.0f);
            caster.getSprite().setMirror(true, 1.0f);

            Vector2 casterPos = caster.getSprite().getPosition();

            Vector2 cardPostion = {
                casterPos.x + 100,
                casterPos.y + 100
            };

            vfxManager.SpawnCardVfx(cardPostion, 1.0f, -90.0f, target, true, false);
        }

    } // namespace CardGuy
} // namespace AbilityManager
