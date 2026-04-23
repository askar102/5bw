#pragma once

#include "../raylib/raylib.h"

class Vfx {
public:
    Vfx() = default;
    Vfx(Vector2 position, float lifetime, Color color = WHITE);
    virtual ~Vfx() = default;

    virtual void Update(float dt);
    virtual void Draw();
    virtual bool IsFinished() const;

    void SetPosition(Vector2 position);
    void SetVelocity(Vector2 velocity);
    void SetLifetime(float lifetime);
    void SetColor(Color color);

    Vector2 GetPosition() const;

protected:
    Vector2 _position = {0.0f, 0.0f};
    Vector2 _velocity = {0.0f, 0.0f};
    float _lifetime = 0.0f;
    float _elapsed = 0.0f;
    Color _color = WHITE;
};
