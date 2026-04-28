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

    // VFX
    Texture2D* CardVFXTexture();

    // cardGuy
    Texture2D* CardAttackTexture();
    Texture2D* CardGuyAtlasTexture();
    
private:
    Texture2D _backgroundTexture = {};
    Texture2D _characterTexture = {};
    Texture2D _enemyTexture = {};
    Texture2D _abilityIconTexture = {};

    // VFX
    Texture2D _cardVFXTexture;

    // cardGuy
    Texture2D _cardAttackTexture = {};
    Texture2D _cardGuyAtlasTexture = {};

    bool _loaded = false;
};
