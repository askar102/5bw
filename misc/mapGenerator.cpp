#include "mapGenerator.h"

using json = nlohmann::json;

std::vector<std::unique_ptr<Sprite>> MapGenerator::GenerateTile(const std::string& path, int tileX, int tileY, Texture2D* treeTexture) 
{
    std::vector<std::unique_ptr<Sprite>> result;

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
                        auto sprite = std::make_unique<Sprite>();

                        sprite->setTexture(treeTexture);
                        sprite->setSize(tileSize, tileSize);
                        sprite->setPosition({
                            (float)tx * tileSize,
                            (float)ty * tileSize
                        });

                        sprite->setSolid(true);
                        // width, height
                        sprite->changeSizeOfRect({60, 60});

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