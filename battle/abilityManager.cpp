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

#include "ability.h"
#include "battleSide.h"
#include <cstdio>
#include <vector>

namespace AbilityManager {
    void SpawnAbility(Ability& clickedAbility,
                      VfxManager& vfxManager,
                      BattleEntity& caster,
                      BattleEntity& target,
                      PartyManager& partyManager,
                      StateManager* stateManager)
    {
        if (clickedAbility.GetName() == "cardAttack")
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
            clickedAbility.Execute(caster, target,true);
            caster.actionText.Add(TextFormat("Used %s", clickedAbility.GetName().c_str()), YELLOW);
            target.actionText.Add(TextFormat("Hit by %s", clickedAbility.GetName().c_str()), ORANGE);
            return;
        }

        if (clickedAbility.GetName() == "cardHeal")
        {
            AbilityManager::CardGuy::SpawnCardHeal(vfxManager, caster, target, clickedAbility, partyManager);
            // we are heal in code
            clickedAbility.Execute(caster, target, true, true);
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
            // we do damage in code
            clickedAbility.Execute(caster, target, true);
            return;
        }
        if (clickedAbility.GetName() == "speedSpin")
        {
            AbilityManager::AngryGuy::SpawnSpeedSpin(vfxManager, caster, target, clickedAbility, partyManager);
            // we do damage in code
            clickedAbility.Execute(caster, target, true);
            return;
        }
        if (clickedAbility.GetName() == "scream")
        {
            AbilityManager::AngryGuy::SpawnScream(vfxManager, caster, target, clickedAbility, partyManager, stateManager);
            // we do damage in code
            clickedAbility.Execute(caster, target, true);
            return;
        }

        // sigmaMen
        if (clickedAbility.GetName() == "pencilThrow")
        {
            AbilityManager::SigmaMen::SpawnPencilThrow(vfxManager, caster, target, clickedAbility, partyManager);
            clickedAbility.Execute(caster, target, true);
            return;
        }

        if (clickedAbility.GetName() == "penThrow")
        {
            AbilityManager::SigmaMen::SpawnPenThrow(vfxManager, caster, target, clickedAbility, partyManager);
            clickedAbility.Execute(caster, target, true);
            return;
        }

        if (clickedAbility.GetName() == "timestop")
        {
            AbilityManager::SigmaMen::SpawnTimestop(vfxManager, caster, target, clickedAbility, partyManager);
            clickedAbility.Execute(caster, target, true);
            return;
        }


        // forest enemies
        if (clickedAbility.GetName() == "enemyDash")
        {
            AbilityManager::ForestEnemies::SpawnEnemyDash(vfxManager, caster, target, clickedAbility, partyManager);
            // we do damage in code
            clickedAbility.Execute(caster, target, true);
            return;
        }

        
    }

    TargetAbilityDesc MakeTargetDesc(Ability& ability,
        VfxManager& vfxManager,
        PartyManager& partyManager,
        StateManager* stateManager)
    {
        TargetAbilityDesc desc;

        // ── cardBlock — глушим выбранного персонажа ───────────────
        if (ability.GetName() == "cardBlock")
        {
            desc.onConfirm = [&vfxManager, &partyManager](BattleEntity& caster, BattleEntity& target){
                AbilityManager::CardGuy::SpawnCardBlock(vfxManager, caster, target, partyManager);
                caster.actionText.Add("Used cardBlock", YELLOW);
                target.actionText.Add("Stunned!", ORANGE);
            };

            desc.onCancel = []()
            {
                TraceLog(LOG_INFO, "[TargetSelector] cardBlock cancelled");
            };

            return desc;
        }

        // ── Сюда добавляй новые таргет-абилки ─────────────────────
        //
        // if (ability.GetName() == "myNewAbility")
        // {
        //     desc.onConfirm = [&](BattleEntity& caster, BattleEntity& target) { ... };
        //     return desc;
        // }

        // ── Fallback — просто выполняем базовый Ability::Execute ──
        desc.onConfirm = [&ability](BattleEntity& caster, BattleEntity& target){
            ability.Execute(caster, target);
        };

        return desc;
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

            caster.getSprite().SetFrameTime(1, 0, 1.0f);

            const AbilityType bulletType = ability.GetType();
            const int abilityDamage = ability.GetDamage();

            vfxManager.SpawnCardVfx(cardPostion, 5.0f, baseAngle - 10.0f, bulletType, abilityDamage, &partyManager, damageSide, false);
            vfxManager.SpawnCardVfx(cardPostion, 5.0f, baseAngle, bulletType, abilityDamage, &partyManager, damageSide, false);
            vfxManager.SpawnCardVfx(cardPostion, 5.0f, baseAngle + 10.0f, bulletType, abilityDamage, &partyManager, damageSide, false);
        }

        void SpawnCardHeal(VfxManager& vfxManager, BattleEntity& caster, BattleEntity& target, const Ability& ability, PartyManager& partyManager)
        {
            const int countOfClones = 15;

            caster.getSprite().SetFrameTime(2, 0, 1.0f);

            Vector2 casterPos = caster.getSprite().GetPosition();

            Party& party = partyManager.GetParty(caster.isEnemy);
            party.HealAll(ability.GetHeal());

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
            caster.getSprite().SetFrameTime(2, 0, 1.0f);

            Vector2 casterPos = caster.getSprite().GetPosition();

            Vector2 cardPostion = {
                casterPos.x + 50.0f,
                casterPos.y
            };

            target.SetStunEffect(2.0f);

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


        void SpawnCardChoose(VfxManager& vfxManager, BattleEntity& caster, BattleEntity& target, PartyManager& partyManager)
        {
            
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

                touched.Damage(dashDamage, &caster);
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

        void SpawnScream(VfxManager& vfxManager, BattleEntity& caster, BattleEntity& target, const Ability& ability, PartyManager& partyManager, StateManager* stateManager)
        {
            printf("SpawnScream called\n");

            BattleEntity* casterPtr = &caster;
            Party& party = partyManager.GetParty(target.isEnemy);

            // target.SetWeaknessEffect(10, 4.0f);

            casterPtr->minigame.Arm(
                KEY_R,
                /* onSuccess */ [casterPtr, &target, stateManager, &party]() {
                    casterPtr->getSprite().SetShaking(true);

                    casterPtr->getSprite().SetFrameTime(2, 0, 1.0f);
                    party.SetScreamEffectAll(4.0f);

                    int bonus = 25;
                    party.DamageAll(bonus);

                    // target.EnemyHitAnimation();
                    casterPtr->actionText.Add("SCREAM BONUS!", MAGENTA);
                    target.actionText.Add(TextFormat("-%d BONUS", bonus), RED);

                    auto scene = std::make_unique<SceneState>(
                        3.0f,               
                        []() {},            
                        [] (SceneContext& ctx) {
                            if (ctx.elapsed < 0.5f)
                            {
                                float t = ctx.elapsed / 0.5f; // 0..1
                                ctx.camera.position.z = 6.0f - t * 2.0f; // 6 -> 4
                                ctx.entity->getSprite().SetShaking(true, 1.0f);
                            }                    
                        },
                        casterPtr,          
                        SceneCameraConfig{} 
                    );

                    stateManager->PushState(std::move(scene));
                },
                /* onFail */ [casterPtr, &target, &party]() {
                    casterPtr->actionText.Add("Missed timing...", GRAY);
                    party.SetScreamEffectAll(4.0f);
                    casterPtr->getSprite().SetShaking(true);

                    casterPtr->getSprite().SetFrameTime(2, 0, 1.0f);
                },
                [casterPtr, &target, &party] () {
                    casterPtr->getSprite().SetFrameTime(2, 0, 1.0f);

                    party.SetScreamEffectAll(4.0f);
                    casterPtr->getSprite().SetShaking(true);

                }
            );
        
        }
    } // namespace AngryGuy

    namespace SigmaMen {
        void SpawnPencilThrow(VfxManager& vfxManager, BattleEntity& caster, BattleEntity& target, const Ability& ability, PartyManager& partyManager)
        {            
            BulletEntity* bullet = vfxManager.SpawnBullet(
                &Game::GetResources().Get("pencil"),
                caster.getSprite().GetPosition(),
                (caster.facing == FacingDirection::Right) ? 0.0f : 180.0f,
                500.0f,                          
                5.0f,                            
                AbilityType::BulletDefault,
                DamageSideForCaster(caster.isEnemy),
                &partyManager
            );
            bullet->SetPartyManager(&partyManager);


            bullet->SetSource(&caster);
            bullet->getSprite().SetSize({100, 100});

            caster.getSprite().SetFrameTime(1, 0, 1.0f);

            int damage = ability.GetDamage();
            // todo: fix it later, hardcore
            bullet->SetBulletType(AbilityType::BulletSplash);
            bullet->TurnDegrees(360.0f, 300.0f, 6);
            bullet->trail.SetEnabled(true);

            bullet->SetOnTouched([damage](BulletEntity& caster, BattleEntity& touched) {
                touched.Damage(damage, caster.GetSource());
                touched.EnemyHitAnimation();
            });
        }
        void SpawnPenThrow(VfxManager& vfxManager, BattleEntity& caster, BattleEntity& target, const Ability& ability, PartyManager& partyManager)
        {
            // то есть летит вперед, когда задела 2-3 игрока, останавливается и крутиться. Она делает сайланс на врагах. Надо ее убить чтобы урать сайланс
            BulletEntity* bullet = vfxManager.SpawnBullet(
                &Game::GetResources().Get("pen"),
                caster.getSprite().GetPosition(),
                (caster.facing == FacingDirection::Right) ? 0.0f : 180.0f,
                500.0f,                          
                5.0f,                            
                AbilityType::BulletDefault,
                DamageSideForCaster(caster.isEnemy),
                &partyManager
            );
            bullet->SetPartyManager(&partyManager);

            bullet->SetSource(&caster);
            bullet->getSprite().SetSize({100, 100});

            caster.getSprite().SetFrameTime(1, 0, 1.0f);

            int damage = ability.GetDamage();
            // todo: fix it later, hardcore
            bullet->SetBulletType(AbilityType::BulletSplash);
            bullet->TurnDegrees(360.0f, 300.0f, 6);
            bullet->trail.SetEnabled(true);

            bullet->SetOnTouched([damage, bullet](BulletEntity& caster, BattleEntity& touched) {
                touched.Damage(damage);

                touched.EnemyHitAnimation();
            });
        }
        void SpawnTimestop(VfxManager& vfxManager, BattleEntity& caster, BattleEntity& target, const Ability& ability, PartyManager& partyManager)
        {
            caster.timestopImmortal = true;
            partyManager.TimestopAll(3.0f, nullptr, false);
        }
    } // sigmaMen
        


    namespace ForestEnemies {
        // todo: шейдер почему то не хавает текстуру врага 0_0
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

                    touched.Damage(dashDamage, &caster);
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
