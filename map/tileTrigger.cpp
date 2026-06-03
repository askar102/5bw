#include "tileTrigger.h"

std::vector<TileScript> TileTrigger::_scripts;

void TileTrigger::AddTileScript(int tileX, int tileY, bool manyTimes, std::function<void()> onEnter, std::function<void()> onExit) 
{
    if (TileScript* existing = FindScript(tileX, tileY))
    {
        existing->onEnter = std::move(onEnter);
        existing->onExit  = std::move(onExit);

        printf("[TileTrigger] script is existing, rewrite...\n");
        return;
    }

    _scripts.push_back({ tileX, tileY, std::move(onEnter), std::move(onExit), manyTimes});

}

TileScript* TileTrigger::FindScript(int tileX, int tileY)
{
    for (TileScript& script : _scripts)
    {
       if (script.tileX == tileX && script.tileY == tileY)
       {
            return &script;
       }
    }
    return nullptr;
}

void TileTrigger::OnEnterTile(int tileX, int tileY)
{
    TileScript* s = FindScript(tileX, tileY);
    if (!s) return;

    printf("[TileTrigger] OnEnter tile script is found (%d, %d)\n", tileX, tileY);

    if (s->onEnter)
    {
        if (!s->manyTimes && s->amountOfUse >= 1)
        {
            printf("[TileTrigger] (%d, %d) Script already used, OnEnter skipped...\n", tileX, tileY);
            return;
        }

        printf("[TileTrigger] (%d, %d) Calling onEnter script...\n", tileX, tileY);
        s->amountOfUse += 1;
        s->onEnter();
    }  
}

void TileTrigger::OnExitTile(int tileX, int tileY)
{
    TileScript* s = FindScript(tileX, tileY);
    if (!s) return;

    printf("[TileTrigger] OnExit tile script is found (%d, %d)\n", tileX, tileY);

    if (s->onExit)
    {
        printf("[TileTrigger] (%d, %d) Calling onExit script...\n", tileX, tileY);
        s->onExit();
    }   
        
}



void TileTrigger::Init()
{
    // EXAMPLE
    AddTileScript(600, 601, false, 
        /*onEnter=*/    [] () {
            printf("Hello\n");
            Npc* npc = NpcManager::Find("angryGuy");
            if (!npc) return;

            npc->MoveTo({400, 300});
            DialogPopUp::Show(nullptr, 1);
        },
        /*onExit=*/     [] () {
            // bla-bla
        }
    );
}

