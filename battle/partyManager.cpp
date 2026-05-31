#include "partyManager.h"

#include <array>

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

/**
 * Эти 2 функции были сделаны нейродауном, видимо он пожелел токены на замену фукнции везде, и сделал
 * просто абстракцию. TODO: refactor
 * 
 */

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
 
// end

// проверяем есть ли под мышкой любой энтити
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
    std::array<BattleEntity*, 8> allEntities{};

    for (size_t i = 0; i < 4; ++i)
    {
        allEntities[i] = _playerParty.Get(i);
        allEntities[i + 4] = _enemyParty.Get(i);
    }

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

    for (BattleEntity* entity : allEntities)
    {
        if (entity)
            entity->CheckTouch(allEntities.data(), allEntities.size());
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

Party& PartyManager::GetParty(bool isEnemy)
{
    return isEnemy ? static_cast<Party&>(_enemyParty)
                   : static_cast<Party&>(_playerParty);
}

void PartyManager::TimestopAll(float duration, std::function<void()> onDone)
{
    GetEnemyParty().SetTimestopEffectAll(duration, onDone);
    GetPlayerParty().SetTimestopEffectAll(duration, onDone);
}