/**
 * @file player.h
 * @author askar102
 * @brief Map player type
 * @date 2026-05-07
 * 
 * @copyright Copyright (c) 2026, askar102
 * 
 */

#pragma once

#include "../raylib/raylib.h"

#include "../item/item.h"

#include "spriteV2.h"

class MapState;

class Player {
public:
    SpriteV2& getSprite() 
    {
        return _sprite;
    }
    
    float getSpeed() const 
    {
        return _speed;
    }

    void setSpeed(float newSpeed) 
    {
        this->_speed = newSpeed;
    }

    void Update(float dt, MapState* map);
    void Draw();

    void SetInScene(bool value);

    bool InScene() const
    {
        return _inScene;
    }

    void Init();

    void EquipItem(Item item);
    Item GetEquippedItem() { return _equippedItem; }

private:
    SpriteV2 _sprite;

    float _speed = 200.0f;

    bool _inScene = false;
    bool _beforeScene = false;
    float _beforeSceneTimer = 0.0f;

    // config
    float _beforeSceneDuration = 0.5f;

    enum class Direction { Down = 0, Left = 1, Right = 2, Up = 3 };
    
    Direction _direction = Direction::Down;
    int _walkFrame = 0; 
    float _animTimer = 0.0f;
    float _animSpeed = 0.15f; 
    bool _isMoving = false;
    
    int GetBaseFrame() const 
    {
        return static_cast<int>(_direction) * 3;
    }

    Item _equippedItem;
};
