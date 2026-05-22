#include "partyManager.h"

void PartyManager::Init()
{
    // Init enemyParty only
    _enemyParty.Init();
}

EnemyParty& PartyManager::GetEnemyParty()
{
    return _enemyParty;
}

PlayerParty& PartyManager::GetPlayerParty()
{
    return _playerParty;
}


BattleEntity* PartyManager::GetSelectedCharacter()
{
    return Game::GetPlayerParty().GetSelectedCharacter();
}

BattleEntity* PartyManager::GetEnemy(size_t index)
{
    return _enemyParty.Get(index);
}

BattleEntity* PartyManager::GetPlayer(size_t index)
{
    return _playerParty.Get(index);
}


void PartyManager::Update(float dt)
{
    for (size_t i = 0; i < 4; ++i)
    {
        BattleEntity* character = _playerParty.Get(i);
        if (character) character->Update(dt);
    }

    for (size_t i = 0; i < 4; ++i)
    {
        BattleEntity* enemy = _enemyParty.Get(i);
        if (enemy) enemy->Update(dt);
    }
}

void PartyManager::Draw()
{
    for (size_t i = 0; i < 4; ++i)
    {
        BattleEntity* character = _playerParty.Get(i);
        if (character) character->Draw();
    }

    for (size_t i = 0; i < 4; ++i)
    {
        BattleEntity* enemy = _enemyParty.Get(i);
        if (enemy) enemy->Draw();
    }
}

void PartyManager::DeselectAll()
{
    _playerParty.DeselectAll();
}

void PartyManager::UpdateSelection()
{
    _playerParty.UpdateSelection();
}