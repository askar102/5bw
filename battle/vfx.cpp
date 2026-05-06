#include "vfx.h"

Vfx::Vfx(Vector2 position, float lifetime, float rotation, TextureResource* textureResource, Color color)
    : _lifetime(lifetime), _color(color)
{
    
    _sprite.SetResource(textureResource);
    

    _sprite.SetPosition(position);
    _sprite.SetRotation(rotation);
    
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
    DrawCircleV(_sprite.GetPosition(), 4.0f, _color);
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

bool Vfx::Hitted()
{
    return _hitTarget;
}