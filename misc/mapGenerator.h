/**
 * @file mapGenerator.h
 * @author askar102
 * @brief Map generator helper
 * @date 2026-05-07
 * 
 * @copyright Copyright (c) 2026, askar102
 * 
 */

#pragma once

#include <cstdint>
#include <vector>
#include <memory>
#include <string>
#include <fstream>
#include <unordered_map>

#include "../raylib/raylib.h"
#include "../external/json.h"

#include "../core/game.h"

#include "../entities/spriteV2.h"
#include "../entities/tree.h"

struct Tile {
    SpriteV2 sprite;
    uint32_t x;
    uint32_t y;
};


class MapGenerator {
public:
    static std::vector<std::unique_ptr<Tile>> GenerateChunk(
        const std::string& path,
        int chunkX,
        int chunkY
    );

    static void Init(TextureResource* tx);
    
private:
    static TextureResource* _tileTexturePack;
};
