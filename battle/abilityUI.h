#pragma once

#include "../entities/sprite.h"
#include "ability.h"

struct AbilityUI {
    Sprite icon;
    Vector2 pos;

    Ability* ability;
    static Texture2D defaultTexture;
};