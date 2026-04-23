#include "battleResources.h"

void BattleResources::Load()
{
    if (_loaded) {
        return;
    }

    _backgroundTexture = LoadTexture("resources/battle.png");
    _characterTexture = LoadTexture("resources/player.png");
    _enemyTexture = LoadTexture("resources/enemy.png");
    _abilityIconTexture = LoadTexture("resources/option.png");
    _loaded = true;
}

void BattleResources::Unload()
{
    if (!_loaded) {
        return;
    }

    UnloadTexture(_backgroundTexture);
    UnloadTexture(_characterTexture);
    UnloadTexture(_enemyTexture);
    UnloadTexture(_abilityIconTexture);
    _loaded = false;
}

Texture2D* BattleResources::BackgroundTexture()
{
    return &_backgroundTexture;
}   

Texture2D* BattleResources::CharacterTexture()
{
    return &_characterTexture;
}

Texture2D* BattleResources::EnemyTexture()
{
    return &_enemyTexture;
}

Texture2D* BattleResources::AbilityIconTexture()
{
    return &_abilityIconTexture;
}
