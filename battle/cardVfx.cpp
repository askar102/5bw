#include <cmath>

#include "cardVfx.h"

CardVfx::CardVfx(Vector2 position, float lifetime, float rotation, Texture2D* texture)
    : Vfx(position, lifetime, rotation, texture, WHITE)
{
}

void CardVfx::OnEnter()
{
    SetSpeed(160.0f);
}

void CardVfx::Update(float dt)
{
    /**
     * for up animation:
     *  const float rotationRad = _sprite.getRotation() * PI / 180.0f;
     *  const Vector2 movement = {
     *      std::cos(rotationRad) * _speed * dt,
     *      std::sin(rotationRad) * _speed * dt
     *  };
     * 
     */

    const Vector2 position = _sprite.getPosition();
    _sprite.setPosition({position.x + _speed * dt, position.y /*+ movement.y*/});

    Vfx::Update(dt);
}

void CardVfx::Draw()
{
    _sprite.Draw();
}

bool CardVfx::IsFinished() const
{
    return Vfx::IsFinished();
}
