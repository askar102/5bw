#include "tileTrigger.h"

void TileTrigger::AddTileScript(int tileX, int tileY, std::function<void()> onEnter, std::function<void()> onExit) 
{
    if (TileScript* existing = FindScript(tileX, tileY))
    {
        existing->onEnter = std::move(onEnter);
        existing->onExit  = std::move(onExit);

        printf("[TileTrigger] script is existing, rewrite");
        return;
    }

    _scripts.push_back({ tileX, tileY, std::move(onEnter), std::move(onExit) });

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

    printf("[TileTrigger] OnEnter tile script is found (%d, %d)", tileX, tileY);

    if (s->onEnter)
    {
        printf("[TileTrigger] (%d, %d) Calling onEnter script...", tileX, tileY);
        s->onEnter();
    }  
}

void TileTrigger::OnExitTile(int tileX, int tileY)
{
    TileScript* s = FindScript(tileX, tileY);
    if (!s) return;

    printf("[TileTrigger] OnExit tile script is found (%d, %d)", tileX, tileY);

    if (s->onExit)
    {
        printf("[TileTrigger] (%d, %d) Calling onExit script...", tileX, tileY);
        s->onExit();
    }   
        
}



void TileTrigger::Init()
{
    // EXAMPLE
    AddTileScript(600, 601, 
        /*onEnter=*/    [] () {
            // bla-bla
        },
        /*onExit=*/     [] () {
            // bla-bla
        }
    );
}

