#include "cardVfx.h"
#include "battleEntity.h"

CardVfx::CardVfx(Vector2 position, float lifetime, float rotation, Texture2D* texture, BattleEntity& target, bool peaceful)
    : Vfx(position, lifetime, rotation, texture, WHITE), _target(&target), _peaceful(peaceful)
{
}

void CardVfx::OnEnter()
{
    SetSpeed(400.0f);
}

void CardVfx::Update(float dt)
{
    const Vector2 position = _sprite.getPosition();

    // DEG2RAD is PI / 180.0f
    float rad = _sprite.getRotation() * DEG2RAD;

    Vector2 direction = {
        std::cosf(rad),
        std::sinf(rad)
    };

    Vector2 nextPosition = {
        position.x + direction.x * _speed * dt,
        position.y + direction.y * _speed * dt
    };

    _sprite.setPosition(nextPosition);

    if (_target && CheckCollisionRecs(_sprite.getRect(), _target->getSprite().getRect()))
    {
        if (!_peaceful)
            _target->EnemyHitAnimation();
        _hitTarget = true;
    }

    const Rectangle projectileRect = _sprite.getRect();
    if (projectileRect.x > static_cast<float>(GetScreenWidth()) ||
        projectileRect.x + projectileRect.width < 0 ||
        projectileRect.y > static_cast<float>(GetScreenHeight()) ||
        projectileRect.y + projectileRect.height < 0)
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
