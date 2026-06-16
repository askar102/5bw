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
#include <algorithm>
#include <cstdint>

TextureResource* MapGenerator::_tileTexturePack = nullptr;
std::unordered_map<int64_t, Chunk> MapGenerator::_chunks;

using json = nlohmann::json;

std::unique_ptr<Chunk> MapGenerator::GenerateChunk(const std::string& path, int32_t chunkX, int32_t chunkY) 
{
    std::unique_ptr<Chunk> resultChunk = std::make_unique<Chunk>();
    std::vector<std::unique_ptr<Tile>> resultTiles;
    std::ifstream file(path);
    if (!file.is_open()) {
        TraceLog(LOG_WARNING, "Chunk file not found: %s", path.c_str());
        resultChunk->tiles = std::move(resultTiles);
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

                // FIXME: hardcore
                if (tileType == 1) { // если четное
                    tile->collide = true;
                }

                resultTiles.push_back(std::move(tile));
            }
        }

        resultChunk->tiles = std::move(resultTiles);
        
        return resultChunk;
    }

    TraceLog(LOG_WARNING, "Chunk %d %d not found in json", chunkX, chunkY);
    resultChunk->tiles = std::move(resultTiles);
    return resultChunk;
}

void MapGenerator::Init(TextureResource* tx) {
    _tileTexturePack = tx;
}

Chunk* MapGenerator::GetChunk(int32_t chunkX, int32_t chunkY)
{
    uint64_t key = ChunkKey(chunkX, chunkY);
    
    auto it = _chunks.find(key);
    if (it != _chunks.end())
        return &it->second;
    
    auto chunk = GenerateChunk("map.json", chunkX, chunkY);
    if (!chunk) return nullptr;
    
    // Adding into _chunks!!!
    Chunk& insertedChunk = _chunks[key]; 

    insertedChunk.x = chunkX;
    insertedChunk.y = chunkY;

    insertedChunk.tiles = std::move(chunk->tiles);
    return &insertedChunk;
}


void MapGenerator::UnloadDistantChunks(int32_t targetChunkX, int32_t targetChunkY, int32_t radius)
{
    for (auto it = _chunks.begin(); it != _chunks.end();) {
        auto& chunk = it->second;

        bool inRadius =  abs((int)chunk.x - (int)targetChunkX) <= (int)radius && 
                         abs((int)chunk.y - (int)targetChunkY) <= (int)radius;
        
        if (!inRadius) TraceLog(LOG_INFO, "Chunk %d %d UNloaded -_-", chunk.x, chunk.y);

        it = inRadius ? std::next(it) :  _chunks.erase(it); 
    }
}

void MapGenerator::LoadDistantChunks(int32_t targetChunkX, int32_t targetChunkY, int32_t radius)
{
    for (int32_t dy = -radius; dy <= radius; ++dy) {
        for (int32_t dx = -radius; dx <= radius; ++dx) {
            int32_t x = targetChunkX + dx;
            int32_t y = targetChunkY + dy;
            int64_t key = ChunkKey(x, y);
            if (!_chunks.count(key)) {
                TraceLog(LOG_INFO, "Chunk %d %d loaded +_+", x, y);
                GetChunk(x, y); 
            }
        }
    }
}

void MapGenerator::ForEachChunk(std::function<void(Chunk&)> pred) {
    for (auto& [id, chunk] : _chunks) {
        pred(chunk);
    }
};