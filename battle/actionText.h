#pragma once

#include "../raylib/raylib.h"

#include <cstddef>
#include <string>
#include <vector>

class ActionText {
public:
    struct Entry {
        std::string text;
        Color color = WHITE;
    };

    void SetAnchor(Vector2 anchor);
    void SetFontSize(int fontSize);
    void SetLineSpacing(float spacing);
    void SetMaxLines(std::size_t maxLines);

    void Add(const std::string& text, Color color = WHITE);
    void SetLine(std::size_t index, const std::string& text, Color color = WHITE);
    void Clear();
    void Draw() const;

private:
    std::vector<Entry> _entries;
    Vector2 _anchor = {0.0f, 0.0f};
    int _fontSize = 10;
    float _lineSpacing = 10.0f;
    float _topOffset = 60.0f;
    std::size_t _maxLines = 10;
};
