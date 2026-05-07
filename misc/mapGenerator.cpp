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

using json = nlohmann::json;

std::vector<std::unique_ptr<SpriteV2>> MapGenerator::GenerateTile(const std::string& path, int tileX, int tileY, TextureResource* treeResource) 
{
    std::vector<std::unique_ptr<SpriteV2>> result;

    std::ifstream file(path);
    if (!file.is_open()) {
        TraceLog(LOG_WARNING, "Chunk not found: %d %d", tileX, tileY);
        return result;
    }

    json data;
    file >> data;

    const int tileSize = 100;

    for (auto& chunk : data["map"]) 
    {
        int x = chunk["x"];
        int y = chunk["y"];

        if (x == tileX && y == tileY) {
            auto tiles = chunk["tile"];
            
            for (int ty = 0; ty < tiles.size(); ++ty) 
            {
                for (int tx = 0; tx < tiles[ty].size(); ++tx) 
                {
                    /**
                    * 0 - Nothing
                    * 1 - Tree
                    */
                    int tileType = tiles[ty][tx];

                    if (tileType == 1) 
                    {
                        auto sprite = std::make_unique<SpriteV2>();

                        sprite->SetResource(treeResource);
                        sprite->SetSize({tileSize, tileSize});
                        sprite->SetPosition({
                            (float)tx * tileSize + tileSize / 2.0f,
                            (float)ty * tileSize + tileSize / 2.0f
                        });

                        sprite->SetCollide(true);
                        // width, height
                        // sprite->SetRectSize({90, 30});

                        result.push_back(std::move(sprite));
                    }
                }
            }

            return result;

        }

    }
    // if the chunk doesnt exits
    // GenerateTile(path, 600, 600, treeTexture);
    return result;
}