#pragma once

#include "ability.h"

#include "../entities/sprite.h"

#include <string>
#include <vector>

class Ability;

class BattleEntity {
public:
    std::string name;
    
    int hp;
    int maxHp;
    
    Sprite sprite;
    bool selected = false;

    std::vector<Ability*> abilities;
    

    bool Alive() const
    {
        return hp > 0; 
    }

    void Draw();

    Sprite& getSprite() 
    {
        return sprite;
    }
};