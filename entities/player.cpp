/**
 * @file player.cpp
 * @author askar102
 * @brief Map player type
 * @date 2026-05-07
 * 
 * @copyright Copyright (c) 2026, askar102
 * 
 */

#include "player.h"
#include "../misc/inputBridge.h"
#include "../item/itemManager.h"

#include "../states/mapState.h"

void Player::SetInScene(bool value)
{
    if (value)
    {
        _beforeScene = true;
        _beforeSceneTimer = _beforeSceneDuration;
        return;
    }

    _beforeScene = false;
    _beforeSceneTimer = 0.0f;
    _inScene = false;
}

void Player::Update(float dt, MapState* map) 
{
    if (_beforeScene)
    {
        _beforeSceneTimer -= dt;
        if (_beforeSceneTimer <= 0.0f)
        {
            _beforeScene = false;
            _beforeSceneTimer = 0.0f;
            _inScene = true;
        }
    }
    if (InScene())
    {
        return;
    }
    if (!map) {
        return;
    }

    float playerSpeed = this->getSpeed();
    Vector2 playerPosition = this->_sprite.GetPosition();
    Vector2 velocity = {0, 0};

    _isMoving = false;

    if (InputBridge::KeyDown(KEY_W)) {
        velocity.y -= playerSpeed * dt;
        _direction = Direction::Up;
        _isMoving = true;
    }
    if (InputBridge::KeyDown(KEY_S)) {
        velocity.y += playerSpeed * dt;
        _direction = Direction::Down;
        _isMoving = true;
    }
    if (InputBridge::KeyDown(KEY_A)) {
        velocity.x -= playerSpeed * dt;
        _direction = Direction::Left;
        _isMoving = true;
    }
    if (InputBridge::KeyDown(KEY_D)) {
        velocity.x += playerSpeed * dt;
        _direction = Direction::Right;
        _isMoving = true;
    }

    Vector2 newPosition = playerPosition;
    newPosition.x += velocity.x;    
    Rectangle rectX = _sprite.GetWorldRect({newPosition.x, playerPosition.y});
    if (!map->CheckCollision(rectX)) {
        playerPosition.x = newPosition.x;
    }
    newPosition = playerPosition;
    newPosition.y += velocity.y;
    Rectangle rectY = _sprite.GetWorldRect({playerPosition.x, newPosition.y});
    if (!map->CheckCollision(rectY)) {
        playerPosition.y = newPosition.y;
    }
    _sprite.SetPosition(playerPosition);

    if (_isMoving)
    {
        _animTimer += dt;
        if (_animTimer >= _animSpeed)
        {
            _animTimer = 0.0f;
            _walkFrame = (_walkFrame + 1) % 3;
        }
    }
    else
    {
        _walkFrame = 1;
        _animTimer = 0.0f;
    }

    _sprite.SetFrame(GetBaseFrame() + _walkFrame);
}

void Player::Draw() 
{
    this->_sprite.Draw();
}

void Player::SetEquipItem(Item item)
{
    _equippedItem = item;
    _hasEquippedItem = true;
}

void Player::UseEquippedItem()
{
    Vector2 textOrigin = {
        _sprite.GetPosition().x,
        _sprite.GetPosition().y - 30.0f
    };

    if (!_hasEquippedItem)
    {
        _sprite.GetText().Show("Nothing to use!", textOrigin, 1.0f, RED);
        return;
    }

    ItemInfo info = ItemManager::GetInfo(_equippedItem.id);

    if (info.type == ItemType::Usable)
    {
        _sprite.GetText().Show("Use!", textOrigin, 1.0f, WHITE);
    }
    else
    {
        _sprite.GetText().Show("Cant use this!", textOrigin, 1.0f, RED);
    }
}

void Player::Init()
{
    
}
