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
    std::string name;
    
    int maxHp = 100;
    int hp = maxHp;
    
    
    Sprite sprite;
    ActionText actionText;

    bool selected = false;
    bool canSelected = true;

    std::vector<std::unique_ptr<Ability>> abilities;
    Texture2D abilityTexture;
    

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
};
