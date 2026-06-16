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
#include <functional>

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

struct Chunk {
    std::vector<std::unique_ptr<Tile>> tiles;
    int32_t x;
    int32_t y;

    Chunk() = default;

    Chunk(const Chunk&) = delete;
    Chunk& operator=(const Chunk&) = delete;

    Chunk(Chunk&&) noexcept = default;
    Chunk& operator=(Chunk&&) noexcept = default;
};

class MapGenerator {
public:
    static std::unique_ptr<Chunk> GenerateChunk(
        const std::string& path,
        int32_t chunkX,
        int32_t chunkY
    );

    static void Init(TextureResource* tx);

    static int64_t ChunkKey(int32_t x, int32_t y) {
        // cool, right?
        return ((int64_t)x << 32) | (uint32_t)y;
    }

    static Chunk* GetChunk(int32_t chunkX, int32_t chunkY);

    static void LoadDistantChunks(int32_t targetChunkX, int32_t targetChunkY, int32_t radius);
    static void UnloadDistantChunks(int32_t targetChunkX, int32_t targetChunkY, int32_t radius);
    
    static void ForEachChunk(std::function<void(Chunk&)> pred);

private:
    static TextureResource* _tileTexturePack;

    static std::unordered_map<int64_t, Chunk> _chunks;
};
