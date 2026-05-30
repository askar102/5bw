/**
 * @file party.h
 * @author askar102
 * @brief The party system
 * @date 2026-05-07
 * 
 * @copyright Copyright (c) 2026, askar102
 * 
 */

#pragma once

#include <array>
#include <memory>

#include "battleEntity.h"


#include "../misc/configReader.h"

class Party {
public:
    Party() = default;

    void Add(std::unique_ptr<BattleEntity> character, size_t index);
    void Remove(size_t index);
    
    void Clear();
    
    BattleEntity* Get(size_t index);

    virtual Vector2 GetPositionByIndex(size_t index);

    BattleEntity* GetSelectedCharacter();

    void UpdateSelection();
    void DeselectAll();

    // effects
    void DamageAll(int amount, BattleEntity* source = nullptr);
    void HealAll(int amount);

    void SetWeaknessEffectAll(int amount, float duration, std::function<void()> onDone = nullptr);
    void SetScreamEffectAll(float duration, std::function<void()> onDone = nullptr);


protected:
    virtual void Init();

private:
    std::array<std::unique_ptr<BattleEntity>, 4> characters;
};