#pragma once

#include "../entities/sprite.h"
#include "../raylib/raylib.h"
#include "../external/json.h"

#include <vector>
#include <memory>
#include <string>
#include <fstream>

class MapGenerator {
public:
    static std::vector<std::unique_ptr<Sprite>> GenerateTile(
        const std::string& path,
        int tileX,
        int tileY,
        Texture2D* treeTexture
    );
};