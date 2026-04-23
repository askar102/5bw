#pragma once

#include "../entities/sprite.h"
#include "ability.h"

#include <array>
#include <memory>
#include <vector>

class AbilityPanel {
public:
    static constexpr size_t kMaxAbilities = 3;

    void SetIconTexture(Texture2D* texture);
    void SetAbilities(const std::vector<std::unique_ptr<Ability>>& abilities);
    void SetAnchor(Vector2 anchor);
    void SetVisible(bool visible);
    void Update();
    void Draw();

private:
    struct Slot {
        Sprite icon;
        Vector2 pos = {0.0f, 0.0f};
        Ability* ability = nullptr;
    };

    std::array<Slot, kMaxAbilities> _slots;
    size_t _activeSlots = 0;
    Vector2 _anchor = {0.0f, 0.0f};
    bool _visible = false;
};
