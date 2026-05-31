/**
 * @file npcManager.cpp
 * @author askar102
 * @brief Global NPC registry
 * @date 2026-05-31
 *
 * @copyright Copyright (c) 2026, askar102
 *
 */

 #include "npcManager.h"
 #include "../core/game.h"
 
 std::vector<NpcRecord> NpcManager::_records;

 Npc* NpcManager::Register(const std::string& id, int tileX, int tileY)
 {
    if (Npc* existing = Find(id))
    {
        printf("[NpcManager] npc '%s' already registered\n", id.c_str());
        return existing;
    }
 
    NpcRecord record;
    record.id = id;
    record.npc = std::make_unique<Npc>();
    record.tileX = tileX;
    record.tileY = tileY;
 
    Npc* raw = record.npc.get();
    _records.push_back(std::move(record));
 
    printf("[NpcManager] Registered npc '%s' at tile (%d, %d)\n", id.c_str(), tileX, tileY);
    return raw;
 }
 

 std::vector<Npc*> NpcManager::GetForTile(int tileX, int tileY)
 {
    std::vector<Npc*> result;
 
    for (auto& record : _records)
    {
        if (record.tileX == tileX && record.tileY == tileY)
        {
            result.push_back(record.npc.get());
        }
           
    }
 
    return result;
 }
 
 Npc* NpcManager::Find(const std::string& id)
 {
    for (auto& record : _records)
    {
       if (record.id == id)
       {
            return record.npc.get();
       }
    }
    return nullptr;
 }
 

 void NpcManager::MoveTile(const std::string& id, int newTileX, int newTileY)
 {
    for (auto& record : _records)
    {
        if (record.id == id)
        {
           record.tileX = newTileX;
           record.tileY = newTileY;
           TraceLog(LOG_INFO, "[NpcManager] NPC '%s' moved to tile (%d, %d)", id.c_str(), newTileX, newTileY);
           return;
        }
    }
 
    TraceLog(LOG_WARNING, "[NpcManager] MoveTile: NPC '%s' not found", id.c_str());
 }
 
 void NpcManager::Clear()
 {
    _records.clear();
 }
 
// Create a new npc
 void NpcManager::Init()
 {
    // TEMPLATE:
    // {
    //    Npc* newNpc = Register("pidor", 601, 601);
    //    newNpc->GetSprite().SetResource(&Game::GetResources().Get("pidorTexture"));
    //    newNpc->SetPosition({400.0f, 300.0f});
    //    newNpc->SetOnEnter([]() { ... });
    // }
    // PLEASE USE {} FOR NEW CLEAN SCOPE

    {
        Npc* angryGuy = Register("angryGuy", 600, 600);
        angryGuy->GetSprite().SetResource(&Game::GetResources().Get("angryGuy"));
        angryGuy->GetSprite().SetSize({88.0f, 128.0f});
        angryGuy->SetPosition({300.0f, 200.0f});
        angryGuy->SetInteractionRadius(70.0f);
        angryGuy->SetOnEnter([]() {
           TraceLog(LOG_INFO, "[NPC] Npc was clicked");
           MoveTile("angryGuy", 600, 601);
        });
    }
 }