#pragma once

#include <functional>
#include <vector>

#include "npcManager.h"

#include "../dialog/dialogPopup.h"
#include "../misc/configReader.h"

#include "../entities/player.h"

struct TileScript {
    int tileX;
    int tileY;
    
    std::function<void()> onEnter;
    std::function<void()> onExit;

    bool manyTimes = true;
    int amountOfUse = 0;
};


class TileTrigger {
public:
    // scripts checkers
    static void OnEnterTile(int32_t tileX, int32_t tileY);
    static void OnExitTile(int32_t tileX, int32_t tileY);

    // create
    static void AddTileScript(int tileX, int tileY, bool manyTimes, std::function<void()> onEnter, std::function<void()> onExit);

    static TileScript* FindScript(int tileX, int tileY);

    // scripting place
    static void Init();

    // for player manipulation
    static void SetPlayer(Player* player)
    {
        _player = player;
    }

private:    
    static std::vector<TileScript> _scripts;

    static Player* _player;
};