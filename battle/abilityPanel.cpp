#include "abilityPanel.h"
#include <sys/stat.h>

void AbilityPanel::SetIconTexture(TextureResource* newTextureResource)
{
    for (auto& slot : _slots)
    {
        slot.icon.SetResource(newTextureResource);
    }
}

void AbilityPanel::SetAbilities(const std::vector<std::unique_ptr<Ability>>& abilities)
{
    _activeSlots = std::min(abilities.size(), kMaxAbilities);

    // соединяем слоты с абилками
    for (size_t i = 0; i < _activeSlots; ++i)
    {
        _slots[i].ability = abilities[i].get();
    }

    // то есть остальные абилки мы скипаем
    for (size_t i = _activeSlots; i < kMaxAbilities; ++i)
    {
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
    for (size_t i = 0; i < _activeSlots; ++i)
    {
        _slots[i].pos = {
            _anchor.x + 150.0f, 
            // - 100 чтобы чуть чуть повыше анчора был
            _anchor.y + static_cast<float>(i) * 50.0f - 100.0f,
        };
        _slots[i].icon.SetPosition(_slots[i].pos);
    }
}

void AbilityPanel::Draw()
{
    if (!_visible)
    {
        return;
    }

    for (size_t i = 0; i < _activeSlots; ++i)
    {
        auto& slot = _slots[i];
        slot.icon.Draw();

        if (slot.ability)
        {
            // TODO: текст спавниться немного криво, но я думаю мы пофиксим это когда будет более обширно делать gui
            DrawText(
                slot.ability->getName().c_str(),
                static_cast<int>(slot.pos.x),
                static_cast<int>(slot.pos.y),
                20,
                WHITE
            );
        }
    }
}

Ability* AbilityPanel::GetAbilityAt(Vector2 mouse) const
{
    if (!_visible)
    {
        return nullptr;
    }

    for (size_t i = 0; i < _activeSlots; ++i)
    {
        const auto& slot = _slots[i];

        if (slot.ability && CheckCollisionPointRec(mouse, slot.icon.GetRect()))
        {
            return slot.ability;
        }
    }

    return nullptr;
}
