#pragma once

#include "ability.h"

#include "../entities/sprite.h"

#include <string>
#include <vector>
#include <memory>

class Ability;

class BattleEntity {
public:
    std::string name;
    
    int maxHp = 100;
    int hp = maxHp;
    
    
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

    // misc
    void InitText();
};