#include "mapGenerator.h"

using json = nlohmann::json;

std::vector<std::unique_ptr<Sprite>> MapGenerator::Generate(const std::string& path, Texture2D* treeTexture) 
{
    std::vector<std::unique_ptr<Sprite>> result;

    std::ifstream file(path);
    json data;
    file >> data;

    auto map = data["map"][0]; // for start we check only first element

    int mapWidth = map["x"];
    int mapHeight = map["y"];

    auto tiles = map["tile"];

    const int tileSize = 100;

    for (int y = 0; y < tiles.size(); ++y) 
    {
        for (int x = 0; x < tiles[y].size(); ++x) 
        {
            /**
             * 0 - Nothing
             * 1 - Tree
             */
            int tileType = tiles[y][x];

            if (tileType == 1) 
            {
                auto sprite = std::make_unique<Sprite>();

                sprite->setTexture(treeTexture);
                sprite->setSize(tileSize, tileSize);
                sprite->setPosition({
                    (float)x * tileSize,
                    (float)y * tileSize
                });

                result.push_back(std::move(sprite));
            }
        }
    }
    return result;
}