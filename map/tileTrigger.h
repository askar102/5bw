#pragma once

#include <functional>
#include <vector>

#include "npcManager.h"

struct TileScript {
    int tileX;
    int tileY;
    
    std::function<void()> onEnter;
    std::function<void()> onExit;
};


class TileTrigger {
public:
    // scripts checkers
    static void OnEnterTile(int tileX, int tileY);
    static void OnExitTile(int tileX, int tileY);

    // create
    static void AddTileScript(int tileX, int tileY, std::function<void()> onEnter, std::function<void()> onExit);

    static TileScript* FindScript(int tileX, int tileY);

    // scripting place
    static void Init();

private:    
    static std::vector<TileScript> _scripts;
};