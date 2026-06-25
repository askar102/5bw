/**
 * @file npcManager.h
 * @author askar102
 * @brief Global NPC registry — persists across tile loads
 * @date 2026-05-31
 *
 * @copyright Copyright (c) 2026, askar102
 *
 */

 #pragma once

 #include <memory>
 #include <string>
 #include <vector>
 #include <functional>
 
#include "mapEntity.h"
 #include "npc.h"
 
 enum class NpcLoadMode
 {
     LocalChunk,
     Global
 };

 struct NpcRecord {
    std::string id;
    std::unique_ptr<Npc> npc;
    MapLocation pos;

    NpcLoadMode loadMode = NpcLoadMode::Global;
 };

 class NpcManager {
 public:
    static void Init();

    static Npc* Register(const std::string& id, MapLocation pos, NpcLoadMode loadMode = NpcLoadMode::Global);

    static std::vector<Npc*> GetForChunk(int32_t chunkX, int32_t chunkY);

    static Npc* Find(const std::string& id);
 
    static void MoveToLocation(const std::string& id, MapLocation loc);
 
    static void Clear();
 
 private:
    static std::vector<NpcRecord> _records;
 };