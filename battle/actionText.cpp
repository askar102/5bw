#include "actionText.h"

#include <cstddef>

void ActionText::SetAnchor(Vector2 anchor)
{
    _anchor = anchor;
}

void ActionText::SetFontSize(int fontSize)
{
    _fontSize = fontSize;
}

void ActionText::SetLineSpacing(float spacing)
{
    _lineSpacing = spacing;
}

void ActionText::SetMaxLines(std::size_t maxLines)
{
    _maxLines = maxLines;
    if (_entries.size() > _maxLines)
    {
        _entries.erase(_entries.begin(), _entries.end() - static_cast<std::ptrdiff_t>(_maxLines));
    }
}

void ActionText::Add(const std::string& text, Color color)
{
    _entries.push_back({text, color});

    if (_entries.size() > _maxLines)
    {
        _entries.erase(_entries.begin());
    }
}

void ActionText::SetLine(std::size_t index, const std::string& text, Color color)
{
    if (index >= _entries.size())
    {
        _entries.resize(index + 1);
    }

    _entries[index] = {text, color};
}

void ActionText::Clear()
{
    _entries.clear();
}

void ActionText::Draw() const
{
    for (std::size_t i = 0; i < _entries.size(); ++i)
    {
        const auto& entry = _entries[i];
        if (entry.text.empty())
        {
            continue;
        }

        float y = _anchor.y - _topOffset - static_cast<float>(i) * _lineSpacing;

        DrawText(
            entry.text.c_str(),
            static_cast<int>(_anchor.x),
            static_cast<int>(y),
            _fontSize,
            entry.color
        );
    }
}
