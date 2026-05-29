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
        if (clickedAbility.GetName() == "speedSpin")
        {
            AbilityManager::AngryGuy::SpawnSpeedSpin(vfxManager, caster, target, clickedAbility, partyManager);
        }
        if (clickedAbility.GetName() == "scream")
        {
            AbilityManager::AngryGuy::SpawnScream(vfxManager, caster, target, clickedAbility, partyManager);
        }

        // forest enemies
        if (clickedAbility.GetName() == "enemyDash")
        {
            AbilityManager::ForestEnemies::SpawnEnemyDash(vfxManager, caster, target, clickedAbility, partyManager);
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
            // todo: add effect
            // todo: fix frames
            caster.getSprite().SetFrame(1);

            const int dashDamage = ability.GetDamage();
            caster.ResetTouchTracking();
            caster.SetOnTouch([&caster, dashDamage](BattleEntity& touched) {
                if (touched.isEnemy == caster.isEnemy)
                    return;

                touched.Damage(dashDamage);
                touched.EnemyHitAnimation();
                touched.SetWeaknessEffect(10, 4.0f);
                touched.actionText.Add(TextFormat("Hit by %s", "speedDash"), ORANGE);
            });
            
            // left / right check
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

        void SpawnSpeedSpin(VfxManager& vfxManager, BattleEntity& caster, BattleEntity& target, const Ability& ability, PartyManager& partyManager)
        {
            printf("SpawnSpin called\n");

            BattleEntity* casterPtr = &caster;
            const float dashDir = (casterPtr->facing == FacingDirection::Right) ? 1.0f : -1.0f;

            // damage section
            const int spinDamage = ability.GetDamage();
            casterPtr->ResetTouchTracking();
            casterPtr->SetOnTouch([casterPtr, spinDamage](BattleEntity& touched) {
                if (touched.isEnemy == casterPtr->isEnemy)
                    return;

                touched.Damage(spinDamage);
                touched.EnemyHitAnimation();
                touched.actionText.Add(TextFormat("Hit by %s", "spinDash"), ORANGE);
            });

            casterPtr->getSprite().SetFrame(0);

            // animation
            casterPtr->trail.SetEnabled(true);
            casterPtr->MoveTo(casterPtr->startPosition.x + dashDir * 600.0f, 1000.0f, [casterPtr] () {
                casterPtr->MoveTo(casterPtr->startPosition.x, 1000.0f);
            });
            casterPtr->TurnDegrees(360.0f, 720.0f, 3, [casterPtr]() {
                float currentRot = casterPtr->getSprite().GetRotation();
                float remainder  = std::fmod(currentRot, 360.0f);
                if (remainder > 0.001f)
                    casterPtr->TurnDegrees(-remainder, 720.0f, 1);
            
                casterPtr->trail.SetEnabled(false);
                casterPtr->ClearOnTouch();
            });
            
        }

        void SpawnScream(VfxManager& vfxManager, BattleEntity& caster, BattleEntity& target, const Ability& ability, PartyManager& partyManager)
        {
            printf("SpawnScream called\n");

            BattleEntity* casterPtr = &caster;

            // target.SetWeaknessEffect(10, 4.0f);

            casterPtr->minigame.Arm(
                KEY_R,
                /* onSuccess */ [casterPtr, &target]() {
                    casterPtr->getSprite().SetShaking(true);

                    casterPtr->getSprite().SetFrameTime(2, 0, 2.0f);
                    target.SetScreamEffect(4.0f);
                    int bonus = 25;
                    target.Damage(bonus);
                    target.EnemyHitAnimation();
                    casterPtr->actionText.Add("SCREAM BONUS!", MAGENTA);
                    target.actionText.Add(TextFormat("-%d BONUS", bonus), RED);
                },
                /* onFail */ [casterPtr, &target]() {
                    casterPtr->actionText.Add("Missed timing...", GRAY);
                    target.SetScreamEffect(4.0f);
                    casterPtr->getSprite().SetShaking(true);

                    casterPtr->getSprite().SetFrameTime(2, 0, 2.0f);
                },
                [casterPtr, &target] () {
                    target.SetScreamEffect(4.0f);
                    casterPtr->getSprite().SetShaking(true);

                    casterPtr->getSprite().SetFrameTime(2, 0, 2.0f);
                }
            );
        
        }
    } // namespace AngryGuy


    namespace ForestEnemies {
        // todo: шейдер почему то не хавает текстуру врага
        void SpawnEnemyDash(VfxManager& vfxManager, BattleEntity& caster, BattleEntity& target, const Ability& ability, PartyManager& partyManager)
        {
            caster.getSprite().SetFrame(1);
            const int dashDamage = ability.GetDamage();

            // todo: hardcore, fix later
            if (caster.name == "enemy") {
                caster.getSprite().SetAlphaFlashing(true);
            }
            
            caster.getSprite().SetBrighteningUp(4.0f, [&caster, dashDamage] () {
                caster.getSprite().SetBrightness(1.0f);

                caster.getSprite().SetAlphaFlashing(false);
                
                caster.ResetTouchTracking();
                caster.SetOnTouch([&caster, dashDamage](BattleEntity& touched) {
                    if (touched.isEnemy == caster.isEnemy)
                        return;

                    touched.Damage(dashDamage);
                    touched.EnemyHitAnimation();
                    // touched.SetWeaknessEffect(10, 4.0f);
                    touched.actionText.Add(TextFormat("Hit by %s", "speedDash"), ORANGE);
                });
            
                // left / right check
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
            }); 
        }
    }
} // namespace AbilityManager
