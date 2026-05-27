#pragma once

#include "enemyParty.h"
#include "../core/game.h"

class PartyManager {
public:
    void Init();

    EnemyParty& GetEnemyParty();
    PlayerParty& GetPlayerParty();

    BattleEntity* GetSelectedCharacter();
    BattleEntity* GetSelectedEntity();
    BattleEntity* GetAbilityTarget(const BattleEntity& caster);
    BattleEntity* GetEnemy(size_t index = 0);

    BattleEntity* GetPlayer(size_t index = 0);

    void Update(float dt);
    void Draw();

    void DeselectAll();
    void UpdateSelection();

private:
    BattleEntity* FindEntityAtMouse();
    BattleEntity* FindFirstAlive(bool enemies);

    EnemyParty _enemyParty;
    PlayerParty& _playerParty = Game::GetPlayerParty();
    BattleEntity* _abilityTarget = nullptr;
};