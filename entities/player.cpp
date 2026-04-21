#include "player.h"
#include "../states/mapState.h"

void Player::Update(float dt, MapState* map) 
{
    if (!map) {
        return;
    }

    float playerSpeed = this->getSpeed();
    Vector2 playerPosition = this->_sprite.getPosition();

    Vector2 velocity = {0, 0};

    if (IsKeyDown(KEY_W)) velocity.y -= playerSpeed * dt;
    if (IsKeyDown(KEY_S)) velocity.y += playerSpeed * dt;
    if (IsKeyDown(KEY_A)) velocity.x -= playerSpeed * dt;
    if (IsKeyDown(KEY_D)) velocity.x += playerSpeed * dt;

    Vector2 newPosition = playerPosition;

    newPosition.x += velocity.x;

    Rectangle rectX = {
        newPosition.x,
        playerPosition.y,
        _sprite.getSize().x,
        _sprite.getSize().y
    };

    if (!map->CheckCollision(rectX)) {
        playerPosition.x = newPosition.x;
    }

    newPosition = playerPosition;
    newPosition.y += velocity.y;

    Rectangle rectY = {
        playerPosition.x,
        newPosition.y,
        _sprite.getSize().x,
        _sprite.getSize().y
    };

    if (!map->CheckCollision(rectY)) {
        playerPosition.y = newPosition.y;
    }

    _sprite.setPosition(playerPosition);

}

void Player::Draw() 
{
    this->_sprite.Draw();
}
