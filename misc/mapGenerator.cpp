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
#include <cstdint>

TextureResource* MapGenerator::_tileTexturePack = nullptr;
std::unordered_map<uint64_t, Chunk> MapGenerator::_chunks;

using json = nlohmann::json;

std::unique_ptr<Chunk> MapGenerator::GenerateChunk(const std::string& path, uint32_t chunkX, uint32_t chunkY) 
{
    std::unique_ptr<Chunk> resultChunk = std::make_unique<Chunk>();
    std::vector<std::unique_ptr<Tile>> resultTiles;
    std::ifstream file(path);
    if (!file.is_open()) {
        TraceLog(LOG_WARNING, "Chunk file not found: %s", path.c_str());
        resultChunk->tiles = resultTiles;
        return resultChunk;
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
                resultTiles.push_back(std::move(tile));
            }
        }

        resultChunk->tiles = resultTiles;

        
        return resultChunk;
    }

    TraceLog(LOG_WARNING, "Chunk %d %d not found in json", chunkX, chunkY);
    resultChunk->tiles = resultTiles;
    return resultChunk;
}

void MapGenerator::Init(TextureResource* tx) {
    _tileTexturePack = tx;
}

Chunk* MapGenerator::GetChunk(uint32_t chunkX, uint32_t chunkY)
{
    uint64_t key = ChunkKey(chunkX, chunkY);
    
    auto it = _chunks.find(key);
    if (it != _chunks.end())
        return &it->second;
    
    auto chunk = GenerateChunk("map.json", chunkX, chunkY);
    if (!chunk) return nullptr;
    
    _chunks[key] = std::move(*chunk);
    return &_chunks[key];
}


void MapGenerator::UnloadDistantChunks(uint32_t targetChunkX, uint32_t targetChunkY, uint32_t radius)
{
    for (auto it = _chunks.begin(); it != _chunks.end();) {
        auto chunk = it->second;

        bool inRadius =  abs((int)chunk.x - (int)targetChunkX) <= (int)radius && 
                         abs((int)chunk.y - (int)targetChunkY) <= (int)radius;
        
        it = inRadius ? std::next(it) : _chunks.erase(it); 
    }
}