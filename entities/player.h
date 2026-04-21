#pragma once

#include "../raylib/raylib.h"

#include "sprite.h"

class MapState;

class Player {
private:
    Sprite _sprite;
    float _speed = 200.0f;

public:
    /**
     * @brief Get the Sprite object
     * 
     * @return Sprite& 
     */
    Sprite& getSprite() 
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
