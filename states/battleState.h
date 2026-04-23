#pragma once

#include "../core/state.h"
#include "../raylib/raylib.h"
#include "../entities/sprite.h"

#include "../battle/abilityPanel.h"
#include "../battle/battleEntity.h"
#include "../battle/battleResources.h"

class BattleState : public State {
private:
    Sprite _background;
    BattleResources _resources;

    // Temporary single-character test setup.
    std::unique_ptr<BattleEntity> _character;
    std::unique_ptr<BattleEntity> _enemy;

    AbilityPanel _abilityPanel;

public:
    void HandleInput() override;
    void Update(float dt) override;
    void Draw() override;

    void OnEnter() override;
    void OnExit() override;

    void InitBackground();
};