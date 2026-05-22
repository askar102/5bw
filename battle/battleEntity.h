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

#include <string>
#include <vector>
#include <memory>
#include <algorithm>

#include "../entities/spriteV2.h"

#include "ability.h"
#include "actionText.h"

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

    bool selected = false;
    bool canSelected = true;
    bool isEnemy = false;

    std::vector<std::unique_ptr<Ability>> abilities;
    Texture2D abilityTexture;

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

private:
    bool _enemyWhirlActive = false;
    double _enemyWhirlResetAt = 0.0;
};
