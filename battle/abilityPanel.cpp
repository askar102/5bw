#include "abilityPanel.h"

#include <algorithm>

void AbilityPanel::SetIconTexture(Texture2D* texture)
{
    for (auto& slot : _slots) {
        slot.icon.setTexture(texture);
    }
}

void AbilityPanel::SetAbilities(const std::vector<std::unique_ptr<Ability>>& abilities)
{
    _activeSlots = std::min(abilities.size(), kMaxAbilities);

    for (size_t i = 0; i < _activeSlots; ++i) {
        _slots[i].ability = abilities[i].get();
    }

    for (size_t i = _activeSlots; i < kMaxAbilities; ++i) {
        _slots[i].ability = nullptr;
    }
}

void AbilityPanel::SetAnchor(Vector2 anchor)
{
    _anchor = anchor;
}

void AbilityPanel::SetVisible(bool visible)
{
    _visible = visible;
}

void AbilityPanel::Update()
{
    for (size_t i = 0; i < _activeSlots; ++i) {
        _slots[i].pos = {_anchor.x + 90.0f, _anchor.y + static_cast<float>(i) * 50.0f};
        _slots[i].icon.setPosition(_slots[i].pos);
    }
}

void AbilityPanel::Draw()
{
    if (!_visible) {
        return;
    }

    for (size_t i = 0; i < _activeSlots; ++i) {
        auto& slot = _slots[i];
        slot.icon.Draw();

        if (slot.ability) {
            DrawText(
                slot.ability->name.c_str(),
                static_cast<int>(slot.pos.x + 10.0f),
                static_cast<int>(slot.pos.y + 10.0f),
                20,
                WHITE
            );
        }
    }
}
