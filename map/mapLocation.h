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
    static constexpr int32_t CHUNK_TILES_X = 13;
    static constexpr int32_t CHUNK_TILES_Y = 10;

    static Vector2 GetWorldPosition(const MapLocation& loc)
    {
        Vector2 chunkStart = {
            (float)loc.chunkX * CHUNK_TILES_X  * 48,
            -(float)loc.chunkY * CHUNK_TILES_Y * 48
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

    static int32_t GetGlobalTileX(const MapLocation& loc)
    {
        return loc.chunkX * CHUNK_TILES_X + loc.tileX;
    }

    static int32_t GetGlobalTileY(const MapLocation& loc)
    {
        return loc.chunkY * CHUNK_TILES_Y + loc.tileY;
    }

    static int32_t GetTileDistance(const MapLocation& a, const MapLocation& b)
    {
        int32_t dx = std::abs(GetGlobalTileX(a) - GetGlobalTileX(b));
        int32_t dy = std::abs(GetGlobalTileY(a) - GetGlobalTileY(b));
        return std::max(dx, dy);
    }

};