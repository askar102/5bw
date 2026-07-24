#include "typewritter.h"

#include "../misc/inputBridge.h"

void Typewritter::SpawnAt(std::string text, Vector2 position, float speed, bool resetInEnd)
{
    SpawnAt(std::vector<std::string>{std::move(text)}, position, speed, resetInEnd);
}

void Typewritter::SpawnAt(std::vector<std::string> lines, Vector2 position, float speed, bool resetInEnd)
{
    _pos = position;
    _resetInEnd = resetInEnd;
    _queue = std::move(lines);
    _queueIndex = 0;
    _visible = !_queue.empty();

    if (_visible)
    {
        StartLine(_queue[0]);
    }  
}

void Typewritter::StartLine(const std::string& text)
{
    _text = text;
    _charsOpened = 0;
}

void Typewritter::AdvanceQueue()
{
    _queueIndex++;

    if (_queueIndex < _queue.size())
    {
        StartLine(_queue[_queueIndex]);
        return;
    }

    if (_resetInEnd)
    {
        Reset();
    } 
    else
    {
        _visible = false;
    }
}

std::vector<std::string> Typewritter::WrapText(const std::string& text) const
{
    std::vector<std::string> lines;
    if (text.empty()) return lines;

    std::string current;
    std::string word;

    auto pushWord = [&]() {
        if (word.empty()) return;
        std::string candidate = current.empty() ? word : (current + " " + word);

        bool fits = _font
            ? MeasureTextEx(*_font, candidate.c_str(), (float)_fontSize, 2.0f).x <= _maxWidth
            : (float)MeasureText(candidate.c_str(), _fontSize) <= _maxWidth;

        if (fits)
        {
            current = candidate;
        }
        else
        {
            if (!current.empty()) lines.push_back(current);
            current = word;
        }
        word.clear();
    };

    for (char c : text)
    {
        if (c == ' ' || c == '\n')
        {
            pushWord();
            if (c == '\n')
            {
                lines.push_back(current);
                current.clear();
            }
        }
        else
        {
            word += c;
        }
    }
    pushWord();
    if (!current.empty()) lines.push_back(current);

    return lines;
}

void Typewritter::Draw()
{
    if (!_visible) return;

    std::string shown = TextSubtext(_text.c_str(), 0, static_cast<int32_t>(_charsOpened));

    if (!_font || _maxWidth <= 0.0f)
    {
        Text::DrawText(shown, (int)_pos.x, (int)_pos.y, _fontSize, _color);
        return;
    }

    Vector2 cursor = _pos;
    int lineSpacing = _fontSize + 4;

    for (const auto& line : WrapText(shown))
    {
        DrawTextEx(*_font, line.c_str(), cursor, (float)_fontSize, 2.0f, _color);
        cursor.y += (float)lineSpacing;
    }
}

void Typewritter::Update(float dt)
{
    if (!_visible) return;

    _charsOpened += _speed * dt;

    bool fullyShown = _charsOpened >= static_cast<float>(_text.size());

    if (InputBridge::KeyPressed(KEY_ENTER))
    {
        if (fullyShown)
        {
            AdvanceQueue();
        }
        else 
        {
            SkipAnimation();
        }  
    }
}

void Typewritter::Reset()
{
    _visible = false;
    _queue.clear();
    _queueIndex = 0;
    _text.clear();
    _charsOpened = 0;

    if (_inOver) _inOver();
}

void Typewritter::SkipAnimation()
{
    _charsOpened = (float)_text.size();
}

void Typewritter::SetSpeed(float charsPerSecond)
{
    _speed = charsPerSecond;
}
