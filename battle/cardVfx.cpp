#include "cardVfx.h"

CardVfx::CardVfx(Vector2 position, float lifetime, Texture2D* texture)
    : Vfx(position, lifetime, WHITE)
{
    _sprite.setTexture(texture);
}

void CardVfx::OnEnter()
{
    _sprite.setPosition({_position.x, _position.y});
    SetSpeed(160.0f);
}

void CardVfx::Update(float dt)
{
    _position.x += _speed * dt;
    _sprite.setPosition({_position.x, _position.y});

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
