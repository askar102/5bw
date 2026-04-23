#pragma once

#include "../raylib/raylib.h"

class BattleResources {
public:
    void Load();
    void Unload();

    Texture2D* BackgroundTexture();
    Texture2D* CharacterTexture();
    Texture2D* EnemyTexture();
    Texture2D* AbilityIconTexture();
    
private:
    Texture2D _backgroundTexture = {};
    Texture2D _characterTexture = {};
    Texture2D _enemyTexture = {};
    Texture2D _abilityIconTexture = {};
    bool _loaded = false;
};
