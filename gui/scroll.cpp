#include "scroll.h"

#include <algorithm>

#include "../misc/inputBridge.h"
#include "../core/game.h"

// NOTE: unlike other Gui elements, Scroll treats SetPosition() as the
// top-left corner of its viewport (grid layout math is easier that way).

Scroll::Scroll(Vector2 pos, int columns, int visibleRows, float slotSize, float spacing)
    : _columns(columns > 0 ? columns : 1),
      _visibleRows(visibleRows > 0 ? visibleRows : 1),
      _slotSize(slotSize),
      _spacing(spacing)
{
    SetPosition(pos);
}

void Scroll::AddIcon(int id, TextureResource* resource, size_t frame)
{
    Slot slot{ id, SpriteV2() };
    slot.icon.SetResource(resource);
    slot.icon.SetFrame(frame);
    slot.icon.SetSize({ _slotSize - 8.0f, _slotSize - 8.0f });

    _slots.push_back(std::move(slot));
}

void Scroll::RemoveIcon(int id)
{
    _slots.erase(
        std::remove_if(_slots.begin(), _slots.end(), [id](const Slot& s) { return s.id == id; }),
        _slots.end()
    );

    _selectedIds.erase(std::remove(_selectedIds.begin(), _selectedIds.end(), id), _selectedIds.end());
}

void Scroll::Clear()
{
    _slots.clear();
    _selectedIds.clear();
    _scrollRows = 0.0f;
}

bool Scroll::IsSelected(int id) const
{
    return std::find(_selectedIds.begin(), _selectedIds.end(), id) != _selectedIds.end();
}

Rectangle Scroll::GetViewportRect() const
{
    Vector2 pos = _sprite.GetPosition();
    float w = _columns * _slotSize + (_columns - 1) * _spacing;
    float h = _visibleRows * _slotSize + (_visibleRows - 1) * _spacing;
    return { pos.x, pos.y, w, h };
}

Rectangle Scroll::GetSlotFrameRect(int index) const
{
    Vector2 origin = _sprite.GetPosition();

    int row = index / _columns;
    int col = index % _columns;
    float pitch = _slotSize + _spacing;

    return {
        origin.x + col * pitch,
        origin.y + row * pitch - _scrollRows * pitch,
        _slotSize,
        _slotSize
    };
}

float Scroll::MaxScrollRows() const
{
    if (_slots.empty()) return 0.0f;

    int totalRows = (static_cast<int>(_slots.size()) + _columns - 1) / _columns;
    int overflow = totalRows - _visibleRows;

    return overflow > 0 ? static_cast<float>(overflow) : 0.0f;
}

void Scroll::ToggleSelect(int id)
{
    auto it = std::find(_selectedIds.begin(), _selectedIds.end(), id);
    if (it != _selectedIds.end())
    {
        _selectedIds.erase(it);
        if (_onDeselect) _onDeselect(id);
        return;
    }

    if (_maxSelected > 0 && static_cast<int>(_selectedIds.size()) >= _maxSelected)
    {
        int evicted = _selectedIds.front();
        _selectedIds.erase(_selectedIds.begin());
        if (_onDeselect) _onDeselect(evicted);
    }

    _selectedIds.push_back(id);
    if (_onSelect) _onSelect(id);
}

void Scroll::Update()
{
    if (!_visible || _slots.empty()) return;

    Rectangle viewport = GetViewportRect();
    Vector2 mouse = Game::GetWorldMouse();
    bool hovering = CheckCollisionPointRec(mouse, viewport);

    if (hovering)
    {
        float wheel = InputBridge::MouseWheelMove();
        if (wheel != 0.0f)
        {
            _scrollRows -= wheel;

            float maxScroll = MaxScrollRows();
            if (_scrollRows < 0.0f) _scrollRows = 0.0f;
            if (_scrollRows > maxScroll) _scrollRows = maxScroll;
        }
    }

    if (InputBridge::MouseButtonPressed(MOUSE_RIGHT_BUTTON))
    {
        for (int i = 0; i < static_cast<int>(_slots.size()); ++i)
        {
            Rectangle rect = GetSlotFrameRect(i);
            if (!CheckCollisionRecs(rect, viewport)) continue; // scrolled out of view

            if (CheckCollisionPointRec(mouse, rect))
            {
                ToggleSelect(_slots[i].id);
                break;
            }
        }
    }
}

void Scroll::Draw()
{
    if (!_visible) return;

    Rectangle viewport = GetViewportRect();

    BeginScissorMode(
        static_cast<int>(viewport.x), static_cast<int>(viewport.y),
        static_cast<int>(viewport.width), static_cast<int>(viewport.height)
    );

    for (int i = 0; i < static_cast<int>(_slots.size()); ++i)
    {
        Rectangle rect = GetSlotFrameRect(i);
        if (!CheckCollisionRecs(rect, viewport)) continue;

        Slot& slot = _slots[i];

        DrawRectangleRec(rect, BLACK);

        Vector2 center = { rect.x + rect.width * 0.5f, rect.y + rect.height * 0.5f };
        slot.icon.SetPosition(center);
        slot.icon.Draw();

        Color frameColor = IsSelected(slot.id) ? GREEN : BLACK;
        DrawRectangleLinesEx(rect, 3.0f, frameColor);
    }

    EndScissorMode();
}
