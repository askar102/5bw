#pragma once

#include "../entities/sprite.h"
#include "../entities/spriteV2.h"

#include "../raylib/raylib.h"
#include "../external/json.h"

#include <vector>
#include <memory>
#include <string>
#include <fstream>

class MapGenerator {
public:
    static std::vector<std::unique_ptr<SpriteV2>> GenerateTile(
        const std::string& path,
        int tileX,
        int tileY,
        TextureResource* treeResource
    );
};