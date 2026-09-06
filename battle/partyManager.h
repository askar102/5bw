#pragma once

#include "enemyParty.h"
#include "../core/game.h"

class PartyManager {
public:
    void Init();

    EnemyParty& GetEnemyParty();
    PlayerParty& GetPlayerParty();

    // какого хуя у нас 2 индетичных метода сука
    // todo: check
    BattleEntity* GetSelectedCharacter();
    BattleEntity* GetSelectedEntity();
    // какого хуя это тут делает
    //todo: check
    BattleEntity* GetAbilityTarget(const BattleEntity& caster);
    BattleEntity* GetEnemy(size_t index = 0);

    BattleEntity* GetPlayer(size_t index = 0);

    void Update(float dt);
    void Draw();

    void DeselectAll();
    void UpdateSelection();

    Party& GetParty(bool isEnemy);

    // effects
    void TimestopAll(float duration, std::function<void()> onDone = nullptr, bool showUi = true);
    bool isTimeStopped() const { return _timeStopped; }

    // ----- ID WORKFLOW ------
    // for lua bindings
    static int NextEntityId()
    {
        return _entityIdCounter++;
    }

    BattleEntity* FindById(int id);

private:
    //todo: check
    BattleEntity* FindEntityAtMouse();
    BattleEntity* FindFirstAlive(bool enemies);

    EnemyParty _enemyParty;
    PlayerParty& _playerParty = Game::GetPlayerParty();
    BattleEntity* _abilityTarget = nullptr;

    bool _timeStopped = false;
    float _timeStopDuration = 0.0f;

    inline static int _entityIdCounter = 0;
};