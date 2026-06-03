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

#include "../core/game.h"
#include "../core/state.h"

#include "../entities/spriteV2.h"

#include "../battle/abilityPanel.h"
#include "../battle/battleEntity.h"
#include "../battle/abilityManager.h"
#include "../battle/vfxManager.h"

#include "../battle/partyManager.h"

#include "../battle/targetSelector.h"

class BattleState : public State {
public:
    void HandleInput() override;
    void Update(float dt) override;
    void Draw() override;

    void OnEnter() override;
    void OnExit() override;

private:
    SpriteV2 _background;

    void InitBackground();
    void InitEnemyParty();
    void InitPlayerParty();

    AbilityPanel _abilityPanel;
    VfxManager _vfxManager;

    PartyManager _partyManager;

    std::vector<BattleEntity*> GatherAllTargets();
    TargetSelector _targetSelector;
};
