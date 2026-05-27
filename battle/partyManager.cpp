#include "partyManager.h"

void PartyManager::Init()
{
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
    return GetSelectedEntity();
}

BattleEntity* PartyManager::GetSelectedEntity()
{
    if (BattleEntity* selected = _playerParty.GetSelectedCharacter())
        return selected;

    return _enemyParty.GetSelectedCharacter();
}

BattleEntity* PartyManager::FindEntityAtMouse()
{
    const Vector2 mouse = GetMousePosition();

    for (size_t i = 0; i < 4; ++i)
    {
        BattleEntity* character = _playerParty.Get(i);
        if (!character || !character->canSelected)
            continue;

        if (CheckCollisionPointRec(mouse, character->getSprite().GetRect()))
            return character;
    }

    for (size_t i = 0; i < 4; ++i)
    {
        BattleEntity* enemy = _enemyParty.Get(i);
        if (!enemy || !enemy->canSelected)
            continue;

        if (CheckCollisionPointRec(mouse, enemy->getSprite().GetRect()))
            return enemy;
    }

    return nullptr;
}

BattleEntity* PartyManager::FindFirstAlive(bool enemies)
{
    for (size_t i = 0; i < 4; ++i)
    {
        BattleEntity* entity = enemies ? _enemyParty.Get(i) : _playerParty.Get(i);
        if (entity && entity->Alive())
            return entity;
    }

    return nullptr;
}

BattleEntity* PartyManager::GetAbilityTarget(const BattleEntity& caster)
{
    if (_abilityTarget && _abilityTarget->Alive())
    {
        if (!caster.isEnemy && _abilityTarget->isEnemy)
            return _abilityTarget;

        if (caster.isEnemy && !_abilityTarget->isEnemy)
            return _abilityTarget;
    }

    return caster.isEnemy ? FindFirstAlive(false) : FindFirstAlive(true);
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
    _enemyParty.DeselectAll();
    _abilityTarget = nullptr;
}

void PartyManager::UpdateSelection()
{
    BattleEntity* hit = FindEntityAtMouse();
    if (!hit)
        return;

    BattleEntity* selected = GetSelectedEntity();

    if (selected && selected->isEnemy != hit->isEnemy)
    {
        _abilityTarget = hit;
        TraceLog(LOG_INFO, "[PARTY] TARGET %s", hit->name.c_str());
        return;
    }

    if (!hit->selected)
    {
        TraceLog(LOG_INFO, "[PARTY] SELECT %s", hit->name.c_str());
        DeselectAll();
        hit->selected = true;
    }
}
