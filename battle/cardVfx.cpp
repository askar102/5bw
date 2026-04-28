#include "cardVfx.h"

CardVfx::CardVfx(Vector2 position, float lifetime, float rotation, Texture2D* texture, Rectangle targetRect)
    : Vfx(position, lifetime, rotation, texture, WHITE), _targetRect(targetRect)
{
}

void CardVfx::OnEnter()
{
    SetSpeed(160.0f);
}

void CardVfx::Update(float dt)
{
    const Vector2 position = _sprite.getPosition();
    const Vector2 nextPosition = {position.x + _speed * dt, position.y};
    _sprite.setPosition(nextPosition);

    if (CheckCollisionRecs(_sprite.getRect(), _targetRect))
    {
        _hitTarget = true;
    }

    const Rectangle projectileRect = _sprite.getRect();
    if (projectileRect.x > static_cast<float>(GetScreenWidth()))
    {
        _leftScreen = true;
    }

    Vfx::Update(dt);
}

void CardVfx::Draw()
{
    // float t = _elapsed / _lifetime;   // 0 → 1
    // float alpha = 1.0f - t;           // 1 → 0

    // _sprite.SetAlpha(alpha);
    _sprite.Draw();
}

bool CardVfx::IsFinished() const
{
    return _hitTarget || _leftScreen || Vfx::IsFinished();
}
