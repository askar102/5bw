#pragma once

#include <string>
#include <vector>
#include <cstdint>
#include <functional>

#include "../raylib/raylib.h"
#include "../entities/spriteV2.h"

#include "../misc/text.h"

class Typewritter {
public:
    void SpawnAt(std::string text, Vector2 position, float speed = 10.0f, bool resetInEnd = false);
    void SpawnAt(std::vector<std::string> lines, Vector2 position, float speed = 10.0f, bool resetInEnd = false);

    void Reset();
    void SkipAnimation();

    void Draw();
    void Update(float dt);

    void SetSpeed(float charsPerSecond);

    // optional: enables word-wrapping (needs a font that actually has the glyphs
    // you're drawing, eg a cyrillic-loaded one - Text::_font doesn't have those)
    void SetFont(const Font* font) { _font = font; }
    void SetMaxWidth(float maxWidth) { _maxWidth = maxWidth; }
    void SetFontSize(int fontSize) { _fontSize = fontSize; }
    void SetColor(Color color) { _color = color; }

    bool IsFullyShown() const { return _charsOpened >= static_cast<float>(_text.size()); }

    void InOver(std::function<void()> inOver) { _inOver = inOver; }

private:
    void StartLine(const std::string& text);
    void AdvanceQueue();

    std::vector<std::string> WrapText(const std::string& text) const;

    Vector2 _pos;

    std::vector<std::string> _queue;
    size_t _queueIndex = 0;

    std::string _text;

    bool _resetInEnd = false;
    bool _visible = false;
    int32_t _framesCounter = 0;

    float _speed = 10.0f;
    float _charsOpened = 0;

    const Font* _font = nullptr;
    float _maxWidth = 0.0f;
    int _fontSize = 20;
    Color _color = WHITE;

    std::function<void()> _inOver;

};
