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
 
 #include "npc.h"
 
 struct NpcRecord {
    std::string id;
    std::unique_ptr<Npc> npc;
    int tileX = 0;
    int tileY = 0;
 };

 class NpcManager {
 public:
    static void Init();

    static Npc* Register(const std::string& id, int tileX, int tileY);
    
    static std::vector<Npc*> GetForTile(int tileX, int tileY);

    static Npc* Find(const std::string& id);
 
    static void MoveTile(const std::string& id, int newTileX, int newTileY);
 
    static void Clear();
 
 private:
    static std::vector<NpcRecord> _records;
 };