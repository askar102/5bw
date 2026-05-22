#pragma once

#include "enemyParty.h"
#include "../core/game.h"

class PartyManager {
public:
    void Init();

    EnemyParty& GetEnemyParty();
    PlayerParty& GetPlayerParty();

    BattleEntity* GetSelectedCharacter();
    BattleEntity* GetEnemy(size_t index = 0);

    BattleEntity* GetPlayer(size_t index = 0);

    void Update(float dt);
    void Draw();

    void DeselectAll();
    void UpdateSelection();

private:
    EnemyParty _enemyParty;
    PlayerParty& _playerParty = Game::GetPlayerParty();
};