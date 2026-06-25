#include "typewritter.h"

void Typewritter::SpawnAt(std::string text, Vector2 position)
{ 
    _text = text;
    _pos = position;
    _visible = true;
}

void Typewritter::Draw()
{
    if (_visible) {
        DrawText(TextSubtext(_text.c_str(), 0, _framesCounter/10), 210, 160, 20, MAROON);
        if (_framesCounter/10 > _text.size()) {
            _visible = false;
        }
    }
}

void Typewritter::Update(float dt)
{
    if (!_visible) return;
    
    _framesCounter++;
}