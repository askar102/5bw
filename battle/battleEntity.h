/**
 * @file battleEntity.h
 * @author askar102
 * @brief Battle entity type
 * @date 2026-05-07
 * 
 * @copyright Copyright (c) 2026, askar102
 * 
 */

#pragma once

#include <functional>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <unordered_set>

#include "../entities/spriteV2.h"
#include "effectLabel.h"

#include "ability.h"
#include "actionText.h"

#include "../misc/ghostTrail.h"

class Ability;

enum class FacingDirection {
    Left,
    Right
};

class BattleEntity {
public:
    static constexpr float ENEMY_WHIRL_EFFECT = 50.0f;
    static constexpr float ENEMY_WHIRL_PUSH_X = 15.0f;
    static constexpr float ENEMY_WHIRL_DURATION = 0.1f;

    BattleEntity(std::string _name, int _maxHp, bool _isEnemy, bool _canSelected,
         std::vector<Ability> _abilities, FacingDirection _facingDirection = FacingDirection::Right);
    BattleEntity();

    std::string name;
    
    FacingDirection facing;

    int maxHp = 100;
    int hp = maxHp;
    
    SpriteV2 sprite;
    ActionText actionText;
    GhostTrail trail;

    Vector2 startPosition;

    bool selected = false;
    bool canSelected = true;
    bool isEnemy = false;

    std::vector<std::unique_ptr<Ability>> abilities;
    Texture2D abilityTexture;

    EffectLabel effectLabel;

    bool Alive() const
    {
        return hp > 0; 
    }

    // Draw logic
    void Draw();
    void DrawAbilities();

    // Update logic
    void Update(float dt);

    void UpdateAbilities();
    void RefreshActionText();

    SpriteV2& getSprite() 
    {
        return sprite;
    }

    const SpriteV2& getSprite() const
    {
        return sprite;
    }

    // Battle actions
    void Heal(int amount);
    void Damage(int amount);

    // Enemy actions
    void UpdateEnemyWhirl();
    void EnemyHitAnimation();

    // Movement actions
    void MoveTo(float targetX, float speed = 300.0f, std::function<void()> onStop = nullptr);
    void MoveTo(BattleEntity& target, float speed = 300.0f, std::function<void()> onStop = nullptr);
    void UpdateMove(float dt);

    void TurnDegrees(float degrees, float speed = 180.0f, int times = 1, std::function<void()> onDone = nullptr);
    void UpdateTurn(float dt);

    void SetOnTouch(std::function<void(BattleEntity&)> onTouch);
    void ClearOnTouch();
    void ResetTouchTracking();
    void CheckTouch(BattleEntity* const* others, size_t count);

    // Effect actions
    // waekness effect - под battleEntity появляется лейбл weaknessEffect.png,
    // накладывается эффект, который уменьшает урон всех скиллов на amount, на время duration
    void SetWeaknessEffect(int amount, float duration, std::function<void()> onDone = nullptr);
    int GetWeaknessEffect();
    void UpdateWeaknessEffect(float dt);
    // void SetScreamEffect();
    // void SetStunEffect();

private:
    bool _enemyWhirlActive = false;
    float _whirlPushApplied = 0.0f;
    double _enemyWhirlResetAt = 0.0;

    bool _moving = false;
    float _moveTargetX = 0.0f;
    float _moveSpeed = 300.0f;
    std::function<void()> _onStop;

    bool _turning = false;
    float _turnTarget = 0.0f;   
    float _turnDelta = 0.0f;  
    float _turnSpeed = 180.0f;
    int   _turnTimesLeft = 0;
    float _turnDegreesPerPass = 0.0f;
    std::function<void()> _onTurnDone;

    std::function<void(BattleEntity&)> _onTouch;
    std::unordered_set<BattleEntity*> _touchedEntities;

    // effects

    // weakness
    int _weaknessAmount = 0;
    float _weaknessDuration = 0.0f;
    bool _weaknessActive = false;   
    std::function<void()> _weaknessOnDone;
};

