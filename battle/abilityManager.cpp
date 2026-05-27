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

#include "battleSide.h"

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

        // AngryGuy
        if (clickedAbility.GetName() == "speedDash")
        {
            AbilityManager::AngryGuy::SpawnSpeedDash(vfxManager, caster, target, clickedAbility, partyManager);
        }
        
    }


    namespace CardGuy {
        void SpawnCardAttack(VfxManager& vfxManager,
                             BattleEntity& caster,
                             BattleEntity& target,
                             const Ability& ability,
                             PartyManager& partyManager)
        {
            (void)target;

            Vector2 casterPos = caster.getSprite().GetPosition();
            Vector2 cardPostion = {casterPos.x, casterPos.y};
            float baseAngle = (caster.facing == FacingDirection::Right) ? 0.0f : 180.0f;

            const DamageableSide damageSide = DamageSideForCaster(caster.isEnemy);

            caster.getSprite().SetFrame(1);

            const AbilityType bulletType = ability.GetType();
            const int abilityDamage = ability.GetDamage();

            vfxManager.SpawnCardVfx(cardPostion, 5.0f, baseAngle - 10.0f, bulletType, abilityDamage, &partyManager, damageSide, false);
            vfxManager.SpawnCardVfx(cardPostion, 5.0f, baseAngle, bulletType, abilityDamage, &partyManager, damageSide, false);
            vfxManager.SpawnCardVfx(cardPostion, 5.0f, baseAngle + 10.0f, bulletType, abilityDamage, &partyManager, damageSide, false);
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
                    AbilityType::BulletDefault,
                    0,
                    &partyManager,
                    DamageSideForCaster(caster.isEnemy),
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
                AbilityType::BulletDefault,
                0,
                &partyManager,
                DamageSideForCaster(caster.isEnemy),
                true,
                false
            );
        }

    } // namespace CardGuy

    namespace AngryGuy {
        void SpawnSpeedDash(VfxManager &vfxManager, BattleEntity &caster, BattleEntity &target, const Ability &ability, PartyManager &partyManager) 
        {
            // todo: fix frames
            caster.getSprite().SetFrame(2);

            const int dashDamage = ability.GetDamage();
            caster.ResetTouchTracking();
            caster.SetOnTouch([&caster, dashDamage](BattleEntity& touched) {
                if (touched.isEnemy == caster.isEnemy)
                    return;

                touched.Damage(dashDamage);
                touched.EnemyHitAnimation();
                touched.actionText.Add(TextFormat("Hit by %s", "speedDash"), ORANGE);
            });
            
            const float dashDir = (caster.facing == FacingDirection::Right) ? 1.0f : -1.0f;
            float offX = (caster.facing == FacingDirection::Right) ? -100.0f : (float)GetScreenWidth() + 100.0f;

            caster.trail.SetEnabled(true);
            // was startPos + 800.0f
            caster.MoveTo(caster.startPosition.x + dashDir * 800.0f, 1000.0f, [&caster, offX] () {
                caster.getSprite().SetPosition({offX, caster.startPosition.y});
                caster.MoveTo(caster.startPosition.x, 1000.0f, [&caster] () {
                    caster.getSprite().SetFrame(0);
                    caster.trail.SetEnabled(false);
                    caster.ClearOnTouch();
                });

            });

            caster.actionText.Add(TextFormat("Used %s", ability.GetName().c_str()), YELLOW);
        }
    } // namespace AngryGuy
} // namespace AbilityManager
