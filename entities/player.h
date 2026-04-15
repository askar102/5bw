#pragma once

#include "../raylib/raylib.h"

#include "sprite.h"

class Player : public Sprite {
public:
    Vector2 position{400, 300};
    float speed = 200.0f;

    void HandleInput();
    void Update(float dt);
    void Draw() override;
};