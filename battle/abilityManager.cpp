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
    void SpawnAbility(Ability& clickedAbility,
                      VfxManager& vfxManager,
                      BattleEntity& caster,
                      BattleEntity& target,
                      PartyManager& partyManager)
    {
        const AbilityType abilityType = clickedAbility.GetType();

        if (abilityType == AbilityType::BulletDefault ||
            abilityType == AbilityType::BulletSplash)
        {
            AbilityManager::CardGuy::SpawnCardAttack(
                vfxManager,
                caster,
                target,
                clickedAbility,
                partyManager
            );
            /**
             * @ref damage is applied in cardVfx.cpp
             */
            clickedAbility.Execute(caster, target, true);
            caster.actionText.Add(TextFormat("Used %s", clickedAbility.GetName().c_str()), YELLOW);
            target.actionText.Add(TextFormat("Hit by %s", clickedAbility.GetName().c_str()), ORANGE);
            return;
        }

        if (clickedAbility.GetName() == "cardHeal")
        {
            AbilityManager::CardGuy::SpawnCardHeal(vfxManager, caster, target, partyManager);
            clickedAbility.Execute(caster, target);
            return;
        }

        if (clickedAbility.GetName() == "cardBlock")
        {
            AbilityManager::CardGuy::SpawnCardBlock(vfxManager, caster, target, partyManager);
        }
    }


    namespace CardGuy {
        void SpawnCardAttack(VfxManager& vfxManager,
                             BattleEntity& caster,
                             BattleEntity& target,
                             const Ability& ability,
                             PartyManager& partyManager)
        {
            Vector2 casterPos = caster.getSprite().GetPosition();
            Vector2 cardPostion = {
                casterPos.x,
                casterPos.y
            };
            float baseAngle = (caster.facing == FacingDirection::Right) ? 0.0f : 180.0f;

            caster.getSprite().SetFrame(1);

            const AbilityType bulletType = ability.GetType();
            const int abilityDamage = ability.GetDamage();

            vfxManager.SpawnCardVfx(cardPostion, 5.0f, baseAngle - 10.0f, target, bulletType, abilityDamage, &partyManager, false);
            vfxManager.SpawnCardVfx(cardPostion, 5.0f, 0.0f, target, bulletType, abilityDamage, &partyManager, false);
            vfxManager.SpawnCardVfx(cardPostion, 5.0f, baseAngle + 10.0f, target, bulletType, abilityDamage, &partyManager, false);
        }

        void SpawnCardHeal(VfxManager& vfxManager, BattleEntity& caster, BattleEntity& target, PartyManager& partyManager)
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

                vfxManager.SpawnCardVfx(
                    cardPostion,
                    1.0f,
                    -90.0f,
                    target,
                    AbilityType::BulletDefault,
                    0,
                    &partyManager,
                    true
                );
            }
        }   

        void SpawnCardBlock(VfxManager& vfxManager, BattleEntity& caster, BattleEntity& target, PartyManager& partyManager)
        {
            caster.getSprite().SetFrame(2);

            Vector2 casterPos = caster.getSprite().GetPosition();

            Vector2 cardPostion = {
                casterPos.x + 50.0f,
                casterPos.y
            };

            vfxManager.SpawnCardVfx(
                cardPostion,
                1.0f,
                -90.0f,
                target,
                AbilityType::BulletDefault,
                0,
                &partyManager,
                true,
                false
            );
        }

    } // namespace CardGuy
} // namespace AbilityManager
