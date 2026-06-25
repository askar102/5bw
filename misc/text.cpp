#include "text.h"

Font Text::_font{};
bool Text::_inited = false;

void Text::DrawText(const std::string& text, Vector2 pos, int size, Color color, float spacing)
{
    DrawTextEx(_font, text.c_str(), pos, (float)size, spacing, color);
}

void Text::DrawText(const std::string& text, int32_t posX, int32_t posY, int size, Color color, float spacing)
{
    DrawTextEx(_font, text.c_str(),{(float)posX,(float)posY },(float)size, spacing, color);
}

void Text::Init()
{
    if (!_inited)
    {
        _font = LoadFont("resources/fonts/arial.ttf");
        _inited = true;
    }
}