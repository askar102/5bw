#pragma once

#include <cmath>

#include "../raylib/raylib.h"

#include "../entities/sprite.h"

class Vfx {
public:
    Vfx() = default;
    Vfx(Vector2 position, float lifetime, float rotation, Texture2D* texture, Color color = WHITE);
    virtual ~Vfx() = default;

    virtual void OnEnter();
    virtual void Update(float dt);
    virtual void Draw();
    virtual bool IsFinished() const;

    void SetSpeed(float speed);
    void SetLifetime(float lifetime);
    void SetColor(Color color);

    bool Hitted();

protected:
    Sprite _sprite;
    float _speed = 0.0f;
    float _lifetime = 0.0f;
    float _elapsed = 0.0f; // времени истекло
    Color _color = WHITE;

    bool _hitTarget = false;
};
