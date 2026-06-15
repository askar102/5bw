/**
 * @file mapGenerator.cpp
 * @author askar102
 * @brief Map generator helper
 * @date 2026-05-07
 * 
 * @copyright Copyright (c) 2026, askar102
 * 
 */

#include "mapGenerator.h"

TextureResource* MapGenerator::_tileTexturePack = nullptr;

using json = nlohmann::json;

std::vector<std::unique_ptr<Tile>> MapGenerator::GenerateChunk(const std::string& path, int chunkX, int chunkY) 
{
    std::vector<std::unique_ptr<Tile>> result;
    std::ifstream file(path);
    if (!file.is_open()) {
        TraceLog(LOG_WARNING, "Chunk file not found: %s", path.c_str());
        return result;
    }

    json chunks;
    file >> chunks;

    float tileSize = 48.0f;
    Vector2 startPos = {
        (float)chunkX * 13 * tileSize,
        (float)chunkY * 10 * tileSize
    };

    for (auto& chunk : chunks) 
    {
        if (chunk["x"] != chunkX || chunk["y"] != chunkY) continue;

        auto& tileData = chunk["tiles"]; // [ty][tx]

        for (int ty = 0; ty < (int)tileData.size(); ++ty) 
        {
            for (int tx = 0; tx < (int)tileData[ty].size(); ++tx) 
            {
                int tileType = tileData[ty][tx];

                auto tile = std::make_unique<Tile>();
                tile->sprite.SetResource(_tileTexturePack);
                tile->sprite.SetFrame(tileType);
                tile->x = tx;
                tile->y = ty;
                tile->sprite.SetPosition({
                    startPos.x + (float)tx * tileSize + tileSize / 2,
                    startPos.y + (float)ty * tileSize + tileSize / 2
                });
                result.push_back(std::move(tile));
            }
        }
        return result;
    }

    TraceLog(LOG_WARNING, "Chunk %d %d not found in json", chunkX, chunkY);
    return result;
}

void MapGenerator::Init(TextureResource* tx) {
    _tileTexturePack = tx;
}