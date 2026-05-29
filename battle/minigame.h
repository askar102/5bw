#pragma once

#include "../raylib/raylib.h"
#include "../core/resourceManager.h"

#include "../entities/spriteV2.h"

class Minigame {
public:
    void Play();
    void Update(float dt);
    void Draw(SpriteV2& unit);
private:
    SpriteV2 _background;
    SpriteV2 _hole;
    SpriteV2 _cursor;
};