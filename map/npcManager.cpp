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
#include "mapEntity.h"
 
 std::vector<NpcRecord> NpcManager::_records;

 Npc* NpcManager::Register(const std::string& id, MapLocation pos, NpcLoadMode loadMode)
 {
    if (Npc* existing = Find(id))
    {
        TraceLog(LOG_INFO, "[NpcManager] npc '%s' already registered\n", id.c_str());
        return existing;
    }
 
    NpcRecord record;
    record.id = id;
    record.npc = std::make_unique<Npc>();
    record.pos = pos;

    record.npc->SetPosition(pos);
 
    Npc* raw = record.npc.get();
    _records.push_back(std::move(record));
 
    TraceLog(LOG_INFO, "[NpcManager] Registered npc '%s' at tile (%d, %d), chunk (%d, %d)\n", id.c_str(), pos.tileX, pos.tileY, pos.chunkX, pos.chunkY);
    return raw;
 }
 

 std::vector<Npc*> NpcManager::GetForChunk(int32_t chunkX, int32_t chunkY)
 {
    TraceLog(LOG_INFO, "Clled 'GetForChunk'");
    std::vector<Npc*> result;
 
    for (auto& record : _records)
    {
        if (record.loadMode == NpcLoadMode::Global) 
        {
            result.push_back(record.npc.get());
            continue;
        }

        if (record.pos.chunkX == chunkX && record.pos.chunkY == chunkY)
        {
            record.npc->GetSprite().SetAlpha(1.0f);
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
 

 void NpcManager::MoveToLocation(const std::string& id, MapLocation loc)
 {
    for (auto& record : _records)
    {
        if (record.id == id)
        {
           record.pos.chunkX = loc.chunkX;
           record.pos.chunkY = loc.chunkY;
           record.pos.tileX = loc.tileX;
           record.pos.tileY = loc.tileY;
           record.npc->GetSprite().FadeOut(1.0f, [&record, loc] () {
                record.npc->GetSprite().SetAlpha(0.0f);
                record.npc->SetPosition(loc);
           });
           TraceLog(LOG_INFO, "[NpcManager] NPC '%s' moved to tile (%d, %d), chunk (%d, %d)", id.c_str(), loc.tileX, loc.tileY, loc.chunkX, loc.chunkY);
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
        Npc* angryGuy = Register("angryGuy", {0, 0, 5, 0});
        angryGuy->GetSprite().SetResource(&Game::GetResources().Get(TextureID::Player));
        angryGuy->GetSprite().SetFrame(0);
        angryGuy->SetInteractionRadius(2);
        angryGuy->SetOnFirstEnter([angryGuy]() {
           TraceLog(LOG_INFO, "[NPC] Npc was clicked (popup only)");
         //   angryGuy->GetDialogPopUp().Show("...", &angryGuy->GetSprite());
           angryGuy->GetEmotionPopUp().Show(EmotionType::LOVE, PopupSize::BIG, 3.0f);
         //   MoveToLocation("angryGuy", {0, 0, 5, 0});
         //   angryGuy->SetOnEnter([angryGuy]() {
         //        angryGuy->MoveTo({100, 100});
         //   });
        });

        angryGuy->SetOnSecondEnter(true, [angryGuy]() {
            printf("SECOND\n");
        });
    }
 }