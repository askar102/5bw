#include "player.h"

void Player::Update(float dt) 
{
    float playerSpeed = this->getSpeed();
    Vector2 playerPositiion = this->_sprite.getPosition();

    if (IsKeyDown(KEY_W)) playerPositiion.y -= playerSpeed * dt;
    if (IsKeyDown(KEY_S)) playerPositiion.y += playerSpeed * dt;
    if (IsKeyDown(KEY_A)) playerPositiion.x -= playerSpeed * dt;
    if (IsKeyDown(KEY_D)) playerPositiion.x += playerSpeed * dt;

    this->_sprite.setPosition(playerPositiion);
}

void Player::Draw() 
{
    this->_sprite.Draw();
}