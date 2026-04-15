#pragma once
#include "../raylib/raylib.h"

class Sprite {
private:
    // pass



public:
    // todo: more OOP needs to be done
    Vector2 position{0, 0};
    Texture2D texture{0};

    virtual void Draw() {
        DrawTexture(texture, position.x, position.y, WHITE);
    }
};