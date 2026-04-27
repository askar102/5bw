#include "vfx.h"

Vfx::Vfx(Vector2 position, float lifetime, Color color)
    : _position(position),
      _lifetime(lifetime),
      _color(color)
{
}

void Vfx::OnEnter()
{
}

void Vfx::Update(float dt)
{
    _elapsed += dt;
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

void Vfx::SetSpeed(float speed)
{
    _speed = speed;
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
