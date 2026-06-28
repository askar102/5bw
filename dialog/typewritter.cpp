#include "typewritter.h"

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

void Typewritter::Draw()
{
    if (!_visible) return;

    Text::DrawText(TextSubtext(_text.c_str(), 0, static_cast<int32_t>(_charsOpened)), (int)_pos.x, (int)_pos.y, 20, WHITE);
}

void Typewritter::Update(float dt)
{
    if (!_visible) return;

    _charsOpened += _speed * dt;

    bool fullyShown = _charsOpened >= static_cast<float>(_text.size());

    if (IsKeyPressed(KEY_ENTER))
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

    _inOver();
}

void Typewritter::SkipAnimation()
{
    _charsOpened = (float)_text.size();
}

void Typewritter::SetSpeed(float charsPerSecond)
{
    _speed = charsPerSecond;
}