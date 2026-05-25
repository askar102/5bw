/**
 * @file abilityManager.cpp
 * @author askar102
 * @brief Directly calling characters' abilities
 * @date 2026-05-07
 * 
 * @copyright Copyright (c) 2026, askar102
 * 
 */

#include "abilityManager.h"

namespace AbilityManager {
    void SpawnAbility(Ability& clickedAbility, VfxManager& vfxManager, BattleEntity& caster, BattleEntity& target)
    {
        std::string abilityName = clickedAbility.GetName();

        if (abilityName == "cardAttack")
            {
                AbilityManager::CardGuy::SpawnCardAttack(
                    vfxManager,
                    caster,
                    target,
                    clickedAbility.GetDamage()
                );
                /**
                 * @ref we damage enemy at cardVfx.cpp, ~35 line
                 * 
                 */
                clickedAbility.Execute(caster, target, true);
                caster.actionText.Add(TextFormat("Used %s", clickedAbility.GetName().c_str()), YELLOW);
                caster.actionText.Add(TextFormat("Hit by %s", clickedAbility.GetName().c_str()), ORANGE);
                return;
            }

            if (abilityName == "cardHeal")
            {
                AbilityManager::CardGuy::SpawnCardHeal(vfxManager, caster, target);
                clickedAbility.Execute(caster, target);
            }

            if (abilityName == "cardBlock")
            {
                AbilityManager::CardGuy::SpawnCardBlock(vfxManager, caster, target);
            }
    }


    namespace CardGuy {
        void SpawnCardAttack(VfxManager& vfxManager, BattleEntity& caster, BattleEntity& target, int damage)
        {
            Vector2 casterPos = caster.getSprite().GetPosition();
            Vector2 cardPostion = {
                casterPos.x,
                casterPos.y
            };
            float baseAngle = (caster.facing == FacingDirection::Right) ? 0.0f : 180.0f;

            caster.getSprite().SetFrame(1);

            // up
            vfxManager.SpawnCardVfx(cardPostion, 5.0f, baseAngle -10.0f, target, false);

            // mid
            vfxManager.SpawnCardVfx(cardPostion, 5.0f, 0.0f, target, false);

            // down
            vfxManager.SpawnCardVfx(cardPostion, 5.0f, baseAngle + 10.0f, target, false);
        }

        void SpawnCardHeal(VfxManager& vfxManager, BattleEntity& caster, BattleEntity& target)
        {
            const int countOfClones = 15;

            caster.getSprite().SetFrame(2);

            Vector2 casterPos = caster.getSprite().GetPosition();

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

        void SpawnCardBlock(VfxManager& vfxManager, BattleEntity& caster, BattleEntity& target)
        {
            /**
             * TODO: bug, sprite dont change costume, fix later
             * 
             */
            caster.getSprite().SetFrame(2);
            // caster.getSprite().setMirror(true, 1.0f);

            Vector2 casterPos = caster.getSprite().GetPosition();

            Vector2 cardPostion = {
                casterPos.x + 50.0f,
                casterPos.y
            };

            vfxManager.SpawnCardVfx(cardPostion, 1.0f, -90.0f, target, true, false);
        }

    } // namespace CardGuy
} // namespace AbilityManager
