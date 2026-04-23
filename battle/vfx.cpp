#include "vfx.h"

Vfx::Vfx(Vector2 position, float lifetime, Color color)
    : _position(position),
      _lifetime(lifetime),
      _color(color)
{
}

void Vfx::Update(float dt)
{
    _elapsed += dt;
    _position.x += _velocity.x * dt;
    _position.y += _velocity.y * dt;
}

void Vfx::Draw()
{
    DrawCircleV(_position, 4.0f, _color);
}

bool Vfx::IsFinished() const
{
    return _elapsed >= _lifetime;
}

void Vfx::SetPosition(Vector2 position)
{
    _position = position;
}

void Vfx::SetVelocity(Vector2 velocity)
{
    _velocity = velocity;
}

void Vfx::SetLifetime(float lifetime)
{
    _lifetime = lifetime;
}

void Vfx::SetColor(Color color)
{
    _color = color;
}

Vector2 Vfx::GetPosition() const
{
    return _position;
}
