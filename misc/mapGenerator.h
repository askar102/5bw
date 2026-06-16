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
    uint32_t x;
    uint32_t y;

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
        uint32_t chunkX,
        uint32_t chunkY
    );

    static void Init(TextureResource* tx);

    static uint64_t ChunkKey(uint32_t x, uint32_t y) {
        return ((uint64_t)x << 32) | y;
    }

    static Chunk* GetChunk(uint32_t chunkX, uint32_t chunkY);

    static void UnloadDistantChunks(uint32_t targetChunkX, uint32_t targetChunkY, uint32_t radius);
    
    static void ForEachChunk(std::function<void(Chunk&)> pred);

private:
    static TextureResource* _tileTexturePack;

    static std::unordered_map<uint64_t, Chunk> _chunks;
};
