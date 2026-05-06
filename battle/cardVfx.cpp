#include "cardVfx.h"
#include "battleEntity.h"

CardVfx::CardVfx(Vector2 position, float lifetime, float rotation, TextureResource* textureResource, BattleEntity& target, bool peaceful, bool animated)
    : Vfx(position, lifetime, rotation, textureResource, WHITE), _target(&target), _peaceful(peaceful), _animated(animated)
{
}

void CardVfx::OnEnter()
{
    SetSpeed(400.0f);
}

void CardVfx::Update(float dt)
{
    if (_animated)
    {
        const Vector2 position = _sprite.GetPosition();

        // DEG2RAD is PI / 180.0f
        float rad = _sprite.GetRotation() * DEG2RAD;

        Vector2 direction = {
            std::cosf(rad),
            std::sinf(rad)
        };

        Vector2 nextPosition = {
            position.x + direction.x * _speed * dt,
            position.y + direction.y * _speed * dt
        };

        _sprite.SetPosition(nextPosition);

        if (_target && CheckCollisionRecs(_sprite.GetRect(), _target->getSprite().GetRect()))
        {
            if (!_peaceful)
            {
                _target->EnemyHitAnimation();
                /**
                * TODO: make the damage take place in a different place
                * 
                */
                _target->Damage(_DAMAGE_OF_ONE_CARD);
            }  
            _hitTarget = true;
        }

        const Rectangle projectileRect = _sprite.GetRect();
        if (projectileRect.x > static_cast<float>(GetScreenWidth()) ||
            projectileRect.x + projectileRect.width < 0 ||
            projectileRect.y > static_cast<float>(GetScreenHeight()) ||
            projectileRect.y + projectileRect.height < 0)
        {
            _leftScreen = true;
        }
    }
    

    Vfx::Update(dt);
}

void CardVfx::Draw()
{
    // card alpha system
    float t = _elapsed / _lifetime;   // 0 → 1
    float alpha = 1.0f - t;           // 1 → 0

    _sprite.SetAlpha(alpha);
    _sprite.Draw();
}

bool CardVfx::IsFinished() const
{
    return _hitTarget || _leftScreen || Vfx::IsFinished();
}