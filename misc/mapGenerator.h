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

#include <vector>
#include <memory>
#include <string>
#include <fstream>

#include "../raylib/raylib.h"
#include "../external/json.h"

#include "../entities/spriteV2.h"

// todo: make the Tree class
class MapGenerator {
public:
    static std::vector<std::unique_ptr<SpriteV2>> GenerateTile(
        const std::string& path,
        int tileX,
        int tileY,
        TextureResource* treeResource
    );
};