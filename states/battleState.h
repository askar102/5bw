/**
 * @file battleState.h
 * @author askar102
 * @brief Battle scene
 * @date 2026-05-07
 * 
 * @copyright Copyright (c) 2026, askar102
 * 
 */

#pragma once

#include "../raylib/raylib.h"

#include "../core/state.h"

#include "../entities/spriteV2.h"

#include "../battle/abilityPanel.h"
#include "../battle/battleEntity.h"
#include "../battle/abilityManager.h"
#include "../battle/vfxManager.h"

class BattleState : public State {
public:
    void HandleInput() override;
    void Update(float dt) override;
    void Draw() override;

    void OnEnter() override;
    void OnExit() override;

    void InitBackground();

private:
    SpriteV2 _background;

    // Temporary single-character test setup.
    std::unique_ptr<BattleEntity> _character;
    std::unique_ptr<BattleEntity> _enemy;

    AbilityPanel _abilityPanel;
    VfxManager _vfxManager;
};
