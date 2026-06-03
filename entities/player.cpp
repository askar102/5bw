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

#include "../states/mapState.h"
#include <algorithm>

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

    if (IsKeyDown(KEY_W)) velocity.y -= playerSpeed * dt;
    if (IsKeyDown(KEY_S)) velocity.y += playerSpeed * dt;
    if (IsKeyDown(KEY_A)) velocity.x -= playerSpeed * dt;
    if (IsKeyDown(KEY_D)) velocity.x += playerSpeed * dt;

    Vector2 newPosition = playerPosition;

    newPosition.x += velocity.x;    

    Rectangle rectX = _sprite.GetWorldRect({newPosition.x, newPosition.y});

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

}

void Player::Draw() 
{
    this->_sprite.Draw();
}
