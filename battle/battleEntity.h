#pragma once

#include "ability.h"

#include "../entities/sprite.h"

#include <string>
#include <vector>
#include <memory>
#include <algorithm>

class Ability;

class BattleEntity {
public:
    std::string name;
    
    unsigned int maxHp = 100;
    unsigned int hp = maxHp;
    
    
    Sprite sprite;

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

    Sprite& getSprite() 
    {
        return sprite;
    }

    // battle actions
    void Heal(unsigned int amount);
    void Damage(unsigned int amount);

    // misc
    void InitText();
};