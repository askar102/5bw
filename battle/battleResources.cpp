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

    // VFX
    _cardVFXTexture = LoadTexture("resources/card.png");

    // cardGuy
    _cardAttackTexture = LoadTexture("resources/cardAttack.png");
    _cardGuyAtlasTexture = LoadTexture("resources/cardGuy_atlas.png");

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

    // VFX
    UnloadTexture(_cardVFXTexture);

    // cardGuy
    UnloadTexture(_cardAttackTexture);
    UnloadTexture(_cardGuyAtlasTexture);

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

// VFX

Texture2D* BattleResources::CardVFXTexture()
{
    return &_cardVFXTexture;
}

// cardGuy
Texture2D* BattleResources::CardAttackTexture()
{
    return &_cardAttackTexture;
}

Texture2D* BattleResources::CardGuyAtlasTexture()
{
    return &_cardGuyAtlasTexture;
}