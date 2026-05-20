/**
 * @file abilityPanel.h
 * @author askar102
 * @brief Creating ability buttons in front of a character
 * @date 2026-05-07
 * 
 * @copyright Copyright (c) 2026, askar102
 * 
 */

#pragma once

#include <array>
#include <memory>
#include <vector>
#include <algorithm>

#include "../entities/spriteV2.h"

#include "ability.h"

class AbilityPanel {
public:
    static constexpr size_t kMaxAbilities = 3;

    void SetIconTexture(TextureResource* newTextureResource);
    void SetAbilities(const std::vector<std::unique_ptr<Ability>>& abilities);
    void SetAnchor(Vector2 anchor);
    void SetVisible(bool visible);
    void Update();
    void Draw();
    Ability* GetAbilityAt(Vector2 mouse) const;

private:
    struct Slot {
        SpriteV2 icon;
        Vector2 pos = {0.0f, 0.0f};
        Ability* ability = nullptr;
    };

    std::array<Slot, kMaxAbilities> _slots;
    size_t _activeSlots = 0;
    Vector2 _anchor = {0.0f, 0.0f};
    bool _visible = false;
};
