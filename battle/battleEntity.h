#pragma once

#include "ability.h"
#include "actionText.h"

#include "../entities/sprite.h"

#include <string>
#include <vector>
#include <memory>
#include <algorithm>

class Ability;

class BattleEntity {
public:
    static constexpr float ENEMY_WHIRL_EFFECT = 50.0f;
    static constexpr float ENEMY_WHIRL_PUSH_X = 15.0f;
    static constexpr float ENEMY_WHIRL_DURATION = 0.1f;

    std::string name;
    
    int maxHp = 100;
    int hp = maxHp;
    
    
    Sprite sprite;
    ActionText actionText;

    bool selected = false;
    bool canSelected = true;
    bool isEnemy = false;

    std::vector<std::unique_ptr<Ability>> abilities;
    Texture2D abilityTexture;

private:
    bool _enemyWhirlActive = false;
    double _enemyWhirlResetAt = 0.0;

public:
    

    bool Alive() const
    {
        return hp > 0; 
    }

    void Draw();
    void DrawAbilities();
    void UpdateAbilities();
    void RefreshActionText();

    Sprite& getSprite() 
    {
        return sprite;
    }

    const Sprite& getSprite() const
    {
        return sprite;
    }

    // battle actions
    void Heal(int amount);
    void Damage(int amount);

    // Enemy actions
    void UpdateEnemyWhirl();
    void EnemyHitAnimation();

};
