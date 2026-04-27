#include "vfx.h"

Vfx::Vfx(Vector2 position, float lifetime, float rotation, Texture2D* texture, Color color)
    : _lifetime(lifetime), _color(color)
{
    if (texture) {
        _sprite.setTexture(texture);
    }

    _sprite.setPosition(position);
    _sprite.setRotation(rotation);
    
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
    DrawCircleV(_sprite.getPosition(), 4.0f, _color);
}

bool Vfx::IsFinished() const
{
    return _elapsed >= _lifetime;
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