#pragma once

#include <vector>
#include <functional>

#include "gui.h"
#include "../entities/spriteV2.h"
#include "../core/resourceManager.h"

// Generic vertical(-ish) scrollable icon list: mouse wheel scrolls it,
// right click selects an icon (frame turns green). Scroll itself doesn't
// know what it's showing (items, party members, whatever) - the caller
// hands it an arbitrary int id per icon and a callback, so the same class
// can back the inventory today and a character-select list later.
class Scroll : public Gui {
public:
    Scroll(Vector2 pos, int columns = 1, int visibleRows = 3, float slotSize = 48.0f, float spacing = 8.0f);

    void AddIcon(int id, TextureResource* resource, size_t frame = 0);
    void RemoveIcon(int id);
    void Clear();

    // how many icons can be selected at once (1 = single-select, like "item in hand")
    void SetMaxSelected(int maxSelected) { _maxSelected = maxSelected; }
    void SetOnSelect(std::function<void(int id)> callback) { _onSelect = callback; }
    void SetOnDeselect(std::function<void(int id)> callback) { _onDeselect = callback; }

    bool IsSelected(int id) const;
    const std::vector<int>& GetSelected() const { return _selectedIds; }

    void Update() override;
    void Draw() override;

private:
    struct Slot {
        int id;
        SpriteV2 icon;
    };

    std::vector<Slot> _slots;
    std::vector<int> _selectedIds;

    int _columns;
    int _visibleRows;
    float _slotSize;
    float _spacing;

    float _scrollRows = 0.0f;
    int _maxSelected = 1;

    std::function<void(int id)> _onSelect;
    std::function<void(int id)> _onDeselect;

    Rectangle GetViewportRect() const;
    Rectangle GetSlotFrameRect(int index) const; // grid slot, scroll offset applied
    float MaxScrollRows() const;
    void ToggleSelect(int id);
};
