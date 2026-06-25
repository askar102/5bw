#pragma once

#include <cstdint>
#include "../entities/spriteV2.h"

struct MapLocation {
    int32_t chunkX;
    int32_t chunkY;

    int32_t tileX;
    int32_t tileY;
};

struct MapLocator {
    static Vector2 GetWorldPosition(const MapLocation& loc)
    {
        Vector2 chunkStart = {
            (float)loc.chunkX * 13  * 48,
            -(float)loc.chunkY * 10 * 48
        };

        return {
            chunkStart.x + (float)loc.tileX * 48 + 48 / 2.0f,
            chunkStart.y + (float)loc.tileY * 48 + 48 / 2.0f
        };
    }

    static void PlaceSprite(SpriteV2& sprite, const MapLocation& loc)
    {
        sprite.SetPosition(GetWorldPosition(loc));
    }

};