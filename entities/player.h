#pragma once

#include "../raylib/raylib.h"

#include "sprite.h"
#include "spriteV2.h"

class MapState;

class Player {
private:
    SpriteV2 _sprite;
    float _speed = 200.0f;

public:
    /**
     * @brief Get the Sprite object
     * 
     * @return Sprite& 
     */
    SpriteV2& getSprite() 
    {
        return _sprite;
    }
    
    /**
     * @brief Get the Speed object
     * 
     * @return float 
     */
    float getSpeed() const 
    {
        return _speed;
    }

    /**
     * @brief Set the Speed object
     * 
     * @param newSpeed Player new speed
     */
    void setSpeed(float newSpeed) 
    {
        this->_speed = newSpeed;
    }

    void Update(float dt, MapState* map);
    void Draw();
};
